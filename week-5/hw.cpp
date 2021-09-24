#include <unistd.h>
#include <fcntl.h>

const int NORMAL = 0;
const int NOOP = 10;
const int TERMINATE = -10;

class frame {
public:
	void process();

	static frame* opening();
};
class ringbuffer {
	private:
		char* inner;
		char* cur_read;
		char* cur_write;
		char* pos_end;

		char* put_buf;

		bool is_full = false;
		int capacity;
	public:
		ringbuffer(int capacity) {
			this->capacity = capacity;
			this->inner = new char[capacity];
			this->put_buf = new char[capacity];
			this->pos_end = this->inner + capacity;
			this->cur_write = this->cur_read = this->inner;
		}
		~ringbuffer() {
			delete[] this->inner;
		}
	
		int remain() {
			if (is_full) return 0;

			if (this->cur_read < this->cur_write) return this->capacity - (this->cur_write - this->cur_read);
			// return this->capacity - (this->capacity + this->cur_write) - this->cur_read;
			return this->cur_read - this->cur_write;
		}
};
class Game {
private:
	int lastloop_ts = 0; // input과 process에 의해서 시간 지연이 생길 수 있음. 루프 실행 timestamp를 이용해서 sleep 기간을 보정함.
	char* inputs; // 비동기로 처리할 것이기도 하고, frame의 전환에서도 입력을 유실하지 않게 따로 input 버퍼를 가지게 함. 이걸로 입력 처리를 해야함
	int inputs_len = 0;
	frame* current_screen; // 화면 처리의 최대단위. DP의 전략패턴을 이용할 것임. frame 아래에서 직접 다음 screen을 수정할 수도 있음을 주의

	int state = NORMAL; // 현재 게임의 전체상태

public:
	Game() {
		this->current_screen = frame::opening();
		this->inputs = new char[1024];

		// 인풋에 영향을 받으면 안되니까 stdin을 넌블럭킹으로 설정
		fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
	}
	~Game() {
		delete[] this->inputs;
	}
	void input() {
		read(STDIN_FILENO, this->inputs, sizeof(this->inputs));
	}
	int process();
	void render();

	void frame_limit(int fps);

	bool is_run() {
		// if (this->state == TERMINATE) return false;
		// return true;

		return this->state != TERMINATE;
	}
};


int main() {
	Game gameInstance = Game();
	int process_result = NORMAL;

	while (gameInstance.is_run()) {
		gameInstance.input();
		gameInstance.process();
		gameInstance.render();

		gameInstance.frame_limit(60);
	}
}