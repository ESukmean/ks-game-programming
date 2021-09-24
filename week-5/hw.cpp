const int NORMAL = 0;
const int NOOP = 10;
const int TERMINATE = -10;

class frame {
public:
	void process();

	static frame* opening();
};

class Game {
private:
	int last_render_ts = 0;
	short* inputs;
	frame* current_screen;
	
public:
	Game() {
		this->current_screen = frame::opening();
		this->inputs = new short[1024];
	}
	~Game() {
		delete[] this->inputs;
	}
	void input();
	int process();
	void render();

	void frame_limit(int fps);

	bool is_run();


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