#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <termios.h>
#include <wchar.h>
#include <time.h>


class Frame;
class Component;
class Screen;
class Game;
class ringbuffer;

const int NORMAL = 0;
const int NOOP = 10;
const int TERMINATE = -10;

const int WIDTH = 189;
const int HEIGHT = 50;

class Frame {
public:
	virtual int process(Game*) {}
	virtual void render(Game*) {}
};
class ringbuffer {
	private:
		int* inner;
		int* cur_read;
		int* cur_write;
		int* pos_end;

		int* put_buf;

		bool is_full = false;
		int capacity;
	public:
		ringbuffer(int capacity) {
			this->capacity = capacity;
			this->inner = new int[capacity];
			this->put_buf = new int[capacity];
			this->pos_end = this->inner + capacity;
			this->cur_write = this->cur_read = this->inner;

			// ��ǲ�� ������ ������ �ȵǴϱ� stdin�� �ͺ�ŷ���� ����
			struct termios oldSettings, newSettings;
			tcgetattr( fileno( stdin ), &oldSettings );
			newSettings = oldSettings;
			newSettings.c_lflag &= (~ICANON & ~ECHO);
			tcsetattr( fileno( stdin ), TCSANOW, &newSettings );    

			fcntl(STDIN_FILENO, F_SETFL, fcntl(STDIN_FILENO, F_GETFL) | O_NONBLOCK);
		}
		~ringbuffer() {
			delete[] this->inner;
			delete[] this->put_buf;
		}

		void stdin_read() {
			int result = 0;
			int avilable = this->buffer_avilable();
			int* put_buf = this->put_buf;
			int read_len = 0;
			for (; read_len < avilable; read_len++) {
				if((result = getchar()) == -1) break;
				// printf("--> %d\n", result);
				*put_buf = result;

				put_buf++;
			}
			

			this->put_enque(read_len);		
		}
		int buffer_avilable() {
			if (is_full) return 0;

			if (this->cur_read < this->cur_write) return this->capacity - (this->cur_write - this->cur_read);
			if (this->cur_read == this->cur_write) return this->capacity;
			return this->cur_read - this->cur_write;
		}
		int buffer_length() {
			return this->capacity - this->buffer_avilable();
		}
		// char* put_arr() {
		// 	// 0���� �ʱ�ȭ(����)�� ������.
		// 	memset(this->put_buf, NULL, this->capacity);
		// 	return this->put_buf;
		// }
		void put_enque(int read_len) {
			if (read_len == 0) return;

			// printf("read %s", this->put_buf);
			// printf("read_len %d\n", read_len);

			// if (read_len > this->buffer_avilable()) { ���� ���뷮 �̻����� ������ �������� �׳� drop �ϵ��� ��. �Ʒ����� �ٿ���� üũ �ʿ� }
			if (this->cur_read < this->cur_write) {
				int tail_length = (this->pos_end - this->cur_write);
				int tail_to_write = std::min(tail_length, read_len * (int)sizeof(int));
				memcpy(this->cur_write, this->put_buf, tail_to_write);

				if (tail_to_write < read_len) {
					// �� �� �� ���Ҵٸ�...
					int head_to_write = std::min((read_len - tail_to_write) * (int)sizeof(int), (int)(this->cur_read - this->inner));
					memcpy(this->inner, this->put_buf + tail_to_write, head_to_write);

					this->cur_write = this->inner + head_to_write / sizeof(int);
				} else {
					// ���ʿ� ���ŷ� ���̸�
					this->cur_write += tail_to_write / sizeof(int);
					if (this->cur_write == this->pos_end) this->cur_write = this->inner;
				}
			} else {
				int avilable = this->buffer_avilable();
				int length = std::min(read_len, avilable > 0 ? avilable : this->capacity);
				memcpy(this->cur_write, this->put_buf, length * sizeof(int));

				this->cur_write += length;
				// printf("cur advanced %d\n", this->cur_write - this->inner); 
			}

			if(this->cur_read == this->cur_write) {
				this->is_full = true;
			}
		}

		void print_content() {	
			int length = this->buffer_length();
			// printf("content length %d // ", length);
			if (length == 0) return;

			int* cur = this->cur_read;
			for (int i = 0; i < length; i++) {
				// printf("%#04x() ", *cur);
				cur++;

				if (cur == this->pos_end + 1) cur = this->inner;
			}
			// printf("\n");
		}
};

class Screen {
public:
	wchar_t* framebuffer; // multi-byte ���ڿ� ���
	Screen() {
		this->framebuffer = new wchar_t[WIDTH * HEIGHT];
		clear();
	}
	~Screen() {
		delete[] this->framebuffer;
	}

	void clear(int x, int y, int width, int height) {
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++) {
				framebuffer[(h + y) * WIDTH + w + x] = *L" ";
			}
		}
	}
	void clear() { 
		clear(0, 0, WIDTH, HEIGHT);
	}

	void fill(int x, int y, int length, wchar_t* src) {
		for (int w = 0; w < length; w++) {
			this->framebuffer[(WIDTH * y) + w + x] = src[w];
		}
	}

	virtual int process(Game* state) {

	}
	virtual void render(Game* state) {
		printf("\033[0;0H");
		for (int h = 0; h < 24; h++) {
			printf("%.*S\n", 180, this->framebuffer + (WIDTH * h));
		}
	}
};
class Component : public Frame {
	protected:
		int x, y;
		int width, height;

	public:
		Component(int x, int y, int width, int height) {
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
		virtual int process(Screen* scrn) {}
		virtual void render(Screen* scrn) {}
};
class component_header : public Component {
	private:
		int tick = 5;
		int reverse = 0;

		wchar_t* header = L"             /@@@@@@/             @@@@@&%/           #@@@@@@@@@@@&#/*.                  .@@@@@@@@@@@@@@@@@@@@@&#                @@@@@@%.           @@@@@%#                \n            &@@@@@@@@             @@@@@@@*           &@@@@@@@@@@@@@@@@@@@@@                    .@@@@@@@@@@@@@@@/              ,@@@@@@@@,          .@@@@@@@                \n           @@@@@@@@%              @@@@@@@            @@@@@@@#      /@@@@@@@                   (@@@@@@@@                      #@@@@@@@@            (@@@@@@@                \n         .@@@@@@@@,    .@%*      ,@@@@@@@            @@@@@@@*      %@@@@@@@                  @@@@@@@@@                      @@@@@@@@@             &@@@@@@@                \n        (@@@@@@@@@@@.  &@@@@@@@@@@@@@@@@@            @@@@@@@.      &@@@@@@%                 @@@@@@@@@@@.                   @@@@@@@@@@@%           @@@@@@@@@@@@@@@@        \n       @@@@@@@@@@@@@@@@#         @@@@@@@@           ,@@@@@@@       @@@@@@@/               ,@@@@@@@@@@@@@@@/              ,@@@@@@@@(@@@@@@@        @@@@@@@, .,*#@@@        \n      @@@@@@@@#    /@@@@@@@      @@@@@@@#           #@@@@@@@       @@@@@@@,              #@@@@@@@@    (@@@@@@@          %@@@@@@@@     @@@@@@@,    @@@@@@@.                \n    ,@@@@@@@@,        .@@@@@     @@@@@@@,           &@@@@@@@%@@@@@@@@@@@@@              @@@@@@@@@        ,@@@@@/       @@@@@@@@&         %@@@@,  ,@@@@@@@                 \n     .%@@@@@                     @@@@@@@            @@@@@@@@@@@@@@%#(.                  /@@@@@@#@@@@@@@*                (@@@@@/                  #@@@@@@@                 \n                        @@&(,,   %%&&@@@                       ..,,*/%&@@@@@                    @@@@@@@                                          /%%&@@@&                 \n                        @@@@@@@@@@@@@@@@@@@@,      (@@@@@@@@@@@@@@@@@@@@@@@@.                  ,@@@@@@@&@@@@@@@@                                                          \n                                     @@@@@@@.               @@@@@@@                    .@@@@@@@@@@@@@@@@@@@@@@@@*                                                         \n                                    ,@@@@@@@         &&#/. (@@@@@@@                                                                                                       \n                        *@@@@@@@@@@@@@@@@@@@        ,@@@@@@@                                                                                                              \n                        %@@@@@@@     ..,,***        #@@@@@@@                                                                                                              \n                        @@@@@@@@                    &@@@@@@&                                                                                                              \n                        @@@@@@@#/%@@@@@@@@@@@@.     @@@@@@@(     .,,*//(%&(                                                                                               \n                        @@@@@@@@@@@@@@&%%/.         @@@@@@@@@@@@@@@@@@@@@@@                                                                                               \n                                                                                                                                                                          \n                                                                                                                                                                          \n                                                                                                                                                                          \n";

	public:
		component_header(int x, int y, int width, int height) : Component(x, y, width, height) {}
		int process(Screen* scrn) {
			if (reverse == 0) {
				tick -= 1;
			} else {
				tick += 1;
			}

			if (tick % 10 == 0) { this->reverse = !(this->reverse); }
		}
		void render(Screen* scrn) {
			int pos_y = tick / 2;
			scrn->clear(0, 0, 170, 24);
			for (int h = 0; h < 24; h++) {
				scrn->fill(0, h + pos_y, 170, header + (170 * h));
			}
		}
};
class screen_opening : public Screen {	
private:
	component_header header = component_header(0, 0, 180, 35);

public:
	int process(Game* state) {
		this->header.process(this);

	}
	void render(Game* state) {
		this->header.render(this);
		Screen::render(state);
	}

};

class Game {
private:
	int lastloop_ts = 0; // input�� process�� ���ؼ� �ð� ������ ���� �� ����. ���� ���� timestamp�� �̿��ؼ� sleep �Ⱓ�� ������.
	int inputs_len = 0;
	ringbuffer inputs = ringbuffer(1024); // �񵿱�� ó���� ���̱⵵ �ϰ�, frame�� ��ȯ������ �Է��� �������� �ʰ� ���� input ���۸� ������ ��. �̰ɷ� �Է� ó���� �ؾ���
	Screen* current_screen; // ȭ�� ó���� �ִ����. DP�� ���������� �̿��� ����. frame �Ʒ����� ���� ���� screen�� ������ ���� ������ ����

	int state = NORMAL; // ���� ������ ��ü����

public:
	Game() {
		this->current_screen = new screen_opening();
	}
	~Game() {
		delete this->current_screen;
	}
	void input() {
		this->inputs.stdin_read();
		
	}
	int process(){
		return this->current_screen->process(this);
	}
	void render(){
		this->current_screen->render(this);
	}

	void frame_limit(int fps){
		int wait_us = 1000000 / fps; // (1 / fps * 1000(us) * 1000(ms))
		usleep(wait_us);
	}

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

		gameInstance.frame_limit(10);
	}
}