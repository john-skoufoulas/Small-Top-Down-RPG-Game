#pragma once
#include "graphics.h"
#include "config.h"
#include "Credits.h"

class StartScreen {
	class Game &EscapeRoom;
	bool gameStart = false;
	bool start_button_down = false;
	bool controls_button_down = false;
	bool credits_button_down = false;
	bool exit_button_down = false;
	bool back_button_down = false;
	bool show_credits = false;
	bool show_controls = false;
	bool exit = false;
	Credits* myCredits = nullptr;
public:
	bool getExit();
	bool getgameStart();
	bool cursor_loc(int high, int low, int right, int left);
	void update();
	void draw();
	StartScreen(class Game& mygame);
	~StartScreen();
};