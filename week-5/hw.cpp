#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <algorithm>
#include <stdio.h>
#include <termios.h>
#include <wchar.h>
#include <time.h>
#include <iostream>
#include <filesystem>
#include <locale.h>	

class Frame;
class Component;
class Screen;
class Game;
class ringbuffer;

const int NORMAL = 0;
const int NOOP = 10;
const int TERMINATE = -10;

const int WIDTH = 237;
const int HEIGHT = 63;

static int escape_key(int k) {
	if (k == -1 || (k & 1792768) != 1792768)  return -1;
	return k & 255;
}
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

			// 인풋에 영향을 받으면 안되니까 stdin을 넌블럭킹으로 설정
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
		// 	// 0으로 초기화(정리)후 던져줌.
		// 	memset(this->put_buf, NULL, this->capacity);
		// 	return this->put_buf;
		// }
		void put_enque(int read_len) {
			if (read_len == 0) return;

			// printf("read %s", this->put_buf);
			// printf("read_len %d\n", read_len);

			// if (read_len > this->buffer_avilable()) { 버퍼 수용량 이상으로 들어오면 마지막은 그냥 drop 하도록 함. 아래에서 바운더리 체크 필요 }
			if (this->cur_read < this->cur_write) {
				int tail_length = (this->pos_end - this->cur_write);
				int tail_to_write = std::min(tail_length, read_len * (int)sizeof(int));
				memcpy(this->cur_write, this->put_buf, tail_to_write);

				if (tail_to_write < read_len) {
					// 쓸 게 더 남았다면...
					int head_to_write = std::min((read_len - tail_to_write) * (int)sizeof(int), (int)(this->cur_read - this->inner));
					memcpy(this->inner, this->put_buf + tail_to_write, head_to_write);

					this->cur_write = this->inner + head_to_write / sizeof(int);
				} else {
					// 뒤쪽에 쓴거로 끝이면
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

				if (cur == this->pos_end) cur = this->inner;
			}
			// printf("\n");
		}

		int get_ch() {
			int length = this->buffer_length();
			if (length == 0) return -1;

			int result = *this->cur_read;

			if ((char)result == '\e' && length >= 3) {
				int check_arr[2] = {0, 0};
				for (int i = 0; i < 2; i++) {
					this->cur_read++;
					if (this->cur_read == this->pos_end) { this->cur_read = this->inner; }

					check_arr[i] = *this->cur_read;
				}

				if ((char)check_arr[0] == '[') {
					result = '\e';
					result = result << 8;
					result += (char)check_arr[0];
					result = result << 8;
					result += (char)check_arr[1];
					// printf("-->%d %d\n", check_arr[0], check_arr[1]);
				}
			}			

			this->cur_read++;
			if (this->is_full) this->is_full = false;
			if (this->cur_read == this->pos_end) this->cur_read = this->inner;

			return result;
		}
		int peek_ch() {
			int length = this->buffer_length();

			if (length == 0) return -1;
			int result = *this->cur_read;

			if ((char)result == '\e' && length >= 3) {
				int check_arr[2] = {0, 0};
				int* cur_tmp = this->cur_read;
				for (int i = 0; i < 2; i++) {
					cur_tmp++;
					if (cur_tmp == this->pos_end) { this->cur_read = this->inner; }

					check_arr[i] = *cur_tmp;
				}

				if ((char)check_arr[0] == '[') {
					result = '\e';
					result = result << 8;
					result += (char)check_arr[0];
					result = result << 8;
					result += (char)check_arr[1];
				}
			}

			return result;
		}
};

class Screen {
public:
	wchar_t* framebuffer; // multi-byte 문자열 고려
	Screen() {
		this->framebuffer = new wchar_t[WIDTH * HEIGHT];
		clear();

		setlocale(LC_ALL, "");
		printf("\e[?25l");
	}
	~Screen() {
		delete[] this->framebuffer;
	}

	void clear(int x, int y, int width, int height) {
		for (int h = 0; h < height; h++) {
			for (int w = 0; w < width; w++) {
				framebuffer[(h + y) * WIDTH + w + x] = L' ';
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
		for (int h = 0; h < HEIGHT; h++) {
			printf("%.*S\n", WIDTH, this->framebuffer + (WIDTH * h));
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
		virtual bool keyinput(Screen* scrn, int keycode) { return false; }
};
class component_header : public Component {
	private:
		int tick = 5;
		int reverse = 0;

		wchar_t* header = L"                                                                                                                       @@@                       @@%(,                 .@@@&#(/*.                @@@                                @@@@@#        @@@@@       .@@@@(/&@@@@@@@             @@@@@%,,/%          @@@@@%       @@@@@                 @@@@@          @@@@@       (@@@@     @@@@&            @@@@@               @@@@@         @@@@@               #@@@@@@@@ ,&@@@@@@@@@&       @@@@@     @@@@*          #@@@@@@@(           #@@@@@@@@       @@@@@@@@@@         @@@@@@  %@@@@    .@@@@*       @@@@@    #@@@@          @@@@@@  @@@@@       @@@@@@  #@@@@   /@@@@.             @@@@@/      .@@   (@@@@        @@@@@@@@@@@@@@         @@@@@@@%(/  #@@     @@@@@(       @@  &@@@@                           #/   &@@@@                  ./##%             @@@@@                           &@@@@                              ,/@@@@@@@@    ,@@@@@@@@@@@@           @@@@@@@@@@@@@@@@                                                             @@@@@            @@*                                                                                  @@@@@@@@@@@@(     @@@@@                                                                                       @@@@@             @@@@@                                                                                      .@@@@@@@@@@@@@@    @@@@@@@@@@@@@@#                                                                                                                                                                           ";
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
			scrn->clear(0, 0, WIDTH, height);
			for (int h = 0; h < 15; h++) {
				scrn->fill(WIDTH / 2 - (this->width / 2), h + pos_y + 3, 110, header + (110 * h));
			}
		}
};
class component_box : public Component {
private:
	bool display_side = true;
public:
	component_box(int x, int y, int width, int height) : Component(x, y, width, height) {}
	~component_box() {}
	int process(Screen* scrn) {
		
	}
	void render(Screen* scrn) {
		for (int w = 0; w < this->width; w++) {
			scrn->framebuffer[(WIDTH * y) + (x + w)] = L'-';
			scrn->framebuffer[(WIDTH * (y + height)) + (x + w)] = L'-';
		}
		if (this->display_side) {
			for (int h = 0; h < this->height; h++) {
				scrn->framebuffer[(WIDTH * (h + y)) + x] = L'│';
				scrn->framebuffer[(WIDTH * (h + y)) + (x + width)] = L'│';
			}
		}

		scrn->framebuffer[(WIDTH * y) + x] = L'┌';
		scrn->framebuffer[(WIDTH * y) + x + width] = L'┐';
		scrn->framebuffer[(WIDTH * (height + y)) + x] = L'└';
		scrn->framebuffer[(WIDTH * (height + y)) + x + width] = L'┘';
	}

	void enable_sidedisplay(bool enabled) {
		this->display_side = enabled;
	}
};
class component_list : public Component {
public:
	wchar_t** list;
	int show_start;
	int show_end;
	int pos = 0;
	int length = 0;
	void refresh_list() {
		namespace fs = std::filesystem;
		std::string path = "./";
		
		if (length > 0) {
			for (int i = 1; i < length; i++) {
				delete list[i];
			}
			delete list;
		}

		list = new wchar_t*[100];
		list[0] = L"새로 만들기...";

		int index = 1;
		for (const auto & entry : fs::directory_iterator(path)) {
			auto path = entry.path().u16string();
			if (path.length() <= 2) continue;

			std::wstring wpath;
			wpath.assign(path.begin(), path.end());

			wchar_t* ws_cloned = new wchar_t[wpath.length()];
			wcpcpy(ws_cloned, wpath.c_str() + 2);

			list[index++] = ws_cloned;

			if (index == 100) break;
		}

		length = index;
		if (pos > length) pos = length - 1;
	}
	component_list(int x, int y, int width, int height) : Component(x, y, width, height) {
		refresh_list();

		show_end = std::min(height, length);
	}
	~component_list() {
		for (int i = 1; i < length; i++) {
			delete list[i];
		}

		delete list;
	}
	bool keyinput(Screen* scrn, int keycode) { 
		switch (escape_key(keycode)) {
			case 'A': // up
				if (pos <= 0) { 
					pos = 0;
					printf("\a");
					break;
				}

				pos--;
				if (show_start > pos) {
					show_start -= 1;
					show_end -= 1;
				}
				break;

			case 'B': // down
				if (pos >= (length - 1)) {
					pos = length - 1;
					printf("\a");
					break;
				}

				pos++;
				if (show_end <= pos) {
					show_start += 1;
					show_end += 1;
				}
				break;
			default:
				printf("\a");
		}
	}
	int process(Screen* scrn) {

	}
	void render(Screen* scrn) {
		scrn->clear(x, y, width, height);

		for (int h = 0; h < std::min(height, this->show_end - this->show_start); h++) {
			if (this->show_start + h == this->pos) 
				scrn->framebuffer[WIDTH * (y + h) + x + 2] = L'@';

			int length = wcslen(this->list[this->show_start + h]);
			scrn->fill(x + 5, y + h, length, this->list[this->show_start + h]);

			wchar_t* null_pos = scrn->framebuffer + (WIDTH * (y + h) + x + 5 + length);
			*null_pos = L' ';
		}
	}
	wchar_t* get_selected() {
		int strlen = wcslen(this->list[this->pos]);
		wchar_t* cloned = new wchar_t[strlen + 1];
		wcscpy(cloned, this->list[this->pos]);

		return cloned;
	}
	int get_selected_pos() {
		return this->pos;
	}
};
class component_line : public Component {
public:
	component_line(int x, int y, int width, int height) : Component(x, y, width, height) {}

	int process(Screen* scrn) {}
	void render(Screen* scrn) {
		for (int h = 0; h < this->height; h++) {
			for (int w = 0; w < this->width / 4; w++) {
				scrn->framebuffer[(WIDTH * (y + h)) + (x + w)] = L'■';
			}
		}
	}
};
class component_text : public Component {
wchar_t* msg = 0;
wchar_t* alert = 0;
int alert_tick = 20;
public:
	component_text(int x, int y, int width, int height) : Component(x, y, width, height) {

	}

	int process(Screen* scrn) {
		if(alert_tick < 20) alert_tick++;
	}
	void render(Screen* scrn) {
		scrn->clear(x, y, width, height);

		if (alert_tick < 20 && this->alert != 0) {
			scrn->fill(x, y, std::min(this->width, (int)wcslen(this->alert)), this->alert);
		} else if(this->msg != 0) {
			scrn->fill(x, y, std::min(this->width, (int)wcslen(this->msg)), this->msg);
		}
	}

	void set_msg(wchar_t* msg) {
		if (this->msg != 0) delete this->msg;
		this->msg = msg;
	}
	void set_alert(wchar_t* alert) {
		if (this->alert != 0) delete this->alert;
		this->alert = alert;
		this->alert_tick = 0;
	}

	static wchar_t* from_const(wchar_t* const msg_const) {
		wchar_t* msg = new wchar_t[wcslen(msg_const) + 1];
		wcscpy(msg, msg_const);

		return msg;
	}
};
class screen_opening : public Screen {	
private:
	component_header header = component_header(0, 0, 110, 27);
	component_box box = component_box(WIDTH / 2 - 100, 28, 200, HEIGHT - 30);
	component_list list = component_list(WIDTH / 2 - 99, 29, 198, HEIGHT - 32);
	component_text txt1 = component_text(WIDTH / 2 - 99, HEIGHT - 1, 100, 1);
	// component_line line = component_line(10, 10, 10, 10);
public:
	screen_opening() {
		this->txt1.set_msg(this->txt1.from_const(L"응답할 설문을 선택하거나 새로 만들어주세요 (엔터: 선택. D: 삭제, 화살표: 이동)"));

		this->box.enable_sidedisplay(false);
	}

	void render(Game* state) {
		this->header.render(this);
		this->box.render(this);
		this->list.render(this);
		this->txt1.render(this);
		Screen::render(state);
	}
	int process(Game* state);
};

class screen_survey : public Screen {
public:
	screen_survey(wchar_t* selected) {
		printf("%S", selected);
		delete selected;
	}
};

class screen_new : public Screen {
	
}
class Game {
private:
	int lastloop_ts = 0; // input과 process에 의해서 시간 지연이 생길 수 있음. 루프 실행 timestamp를 이용해서 sleep 기간을 보정함.
	int inputs_len = 0;

	int state = NORMAL; // 현재 게임의 전체상태

public:
	Screen* current_screen; // 화면 처리의 최대단위. DP의 전략패턴을 이용할 것임. frame 아래에서 직접 다음 screen을 수정할 수도 있음을 주의
	ringbuffer inputs = ringbuffer(1024); // 비동기로 처리할 것이기도 하고, frame의 전환에서도 입력을 유실하지 않게 따로 input 버퍼를 가지게 함. 이걸로 입력 처리를 해야함

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

int screen_opening::process(Game* state) {
	this->header.process(this);
	this->txt1.process(this);

	int key_input = 0;
	while ((key_input = state->inputs.get_ch()) != -1) {
		if (key_input == '\n') {
			state->current_screen = new screen_survey(this->list.get_selected());
			delete this;
		} else if (key_input == 'd' || key_input == 'D') {
			if(this->list.get_selected_pos() == 0) { 
				this->txt1.set_alert(this->txt1.from_const(L"* 새로 만들기 항목은 삭제할 수 없습니다."));
				printf("\a");
				return NORMAL;
			}

			auto filename = this->list.get_selected();
			auto filename_str = std::wstring(L"./").append(filename);
			if (std::filesystem::remove(filename) == 0) {
				this->txt1.set_alert(this->txt1.from_const(L"* 이 파일은 삭제할 수 없습니다."));
				printf("\a");
				return NORMAL;
			}

			this->list.refresh_list();
			delete filename;
		} else {
			this->list.keyinput(this, key_input);
		}
	}
}


int main() {
	Game gameInstance = Game();
	int process_result = NORMAL;

	while (gameInstance.is_run()) {
		gameInstance.input();
		gameInstance.process();
		gameInstance.render();

		int k = gameInstance.inputs.get_ch();
		// printf("%d %d", gameInstance.inputs.peek_ch(),  gameInstance.inputs.get_ch());
		gameInstance.frame_limit(10);
	}
}