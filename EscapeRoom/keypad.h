#pragma once
#include "GameObject.h"

class keypad : public  GameObject {
	bool pressed = false;
	std::string password = "";
	int input1 = -1;
	int input2 = -1;
	int input3 = -1;
	int input4 = -1;
public:
	bool cursor_loc(int high, int low, int right, int left);
	std::string getInput();
	void update() override;
	void draw() override;
	keypad(class Game& mygame);
	~keypad();
};
