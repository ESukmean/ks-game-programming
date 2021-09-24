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
	int lastloop_ts = 0; // input�� process�� ���ؼ� �ð� ������ ���� �� ����. ���� ���� timestamp�� �̿��ؼ� sleep �Ⱓ�� ������.
	char* inputs; // �񵿱�� ó���� ���̱⵵ �ϰ�, frame�� ��ȯ������ �Է��� �������� �ʰ� ���� input ���۸� ������ ��. �̰ɷ� �Է� ó���� �ؾ���
	int inputs_len = 0;
	frame* current_screen; // ȭ�� ó���� �ִ����. DP�� ���������� �̿��� ����. frame �Ʒ����� ���� ���� screen�� ������ ���� ������ ����

	int state = NORMAL; // ���� ������ ��ü����

public:
	Game() {
		this->current_screen = frame::opening();
		this->inputs = new char[1024];

		// ��ǲ�� ������ ������ �ȵǴϱ� stdin�� �ͺ�ŷ���� ����
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