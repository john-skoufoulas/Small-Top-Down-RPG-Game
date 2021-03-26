#include "keypad.h"
#include "iostream"
#include "string"
#include "Game.h"

std::string keypad::getInput() {
	return this->password;
}

void keypad::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (ms.button_left_released) {
		if (cursor_loc(172, 209, 207, 170)) {
			password += "1";
		}
		else if (cursor_loc(172, 209, 258, 220)) {
			password += "2";
		}
		else if (cursor_loc(172, 209, 309, 272)) {
			password += "3";
		}
		if (cursor_loc(224, 260, 207, 170)) {
			password += "4";
		}
		else if (cursor_loc(224, 260, 258, 220)) {
			password += "5";
		}
		else if (cursor_loc(224, 260, 309, 272)) {
			password += "6";
		}
		if (cursor_loc(275, 311, 207, 170)) {
			password += "7";
		}
		else if (cursor_loc(275, 311, 258, 220)) {
			password += "8";
		}
		else if (cursor_loc(275, 311, 309, 272)) {
			password += "9";
		}
		else if (cursor_loc(326, 362, 258, 220)) {
			password += "0";
		}
	}
}

void keypad::draw()
{

	//Draw Keypad
	graphics::Brush br;
	br.texture = "assets\\keypad.png";
	br.outline_opacity = 0;
	graphics::drawRect(CANVAS / 2, CANVAS / 2, 151, 261, br);

	//Draw apearing numbers
	graphics::setFont("assets\\myFont.ttf");
	if (pressed) {
		graphics::drawRect(CANVAS / 2, CANVAS / 2, 20, 20, br);
	}
	if (password.length() >= 1) {
		graphics::drawText(190, 145, 30, password.substr(0, 1), br);
	}
	if (password.length() >= 2) {
		graphics::drawText(220, 145, 30, password.substr(1, 1), br);
	}
	if (password.length() >= 3) {
		graphics::drawText(250, 145, 30, password.substr(2, 1), br);
	}
	if (password.length() >= 4) {
		graphics::drawText(280, 145, 30, password.substr(3, 1), br);
	}
}

bool keypad::cursor_loc(int high, int low, int right, int left)
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	return EscapeRoom.windowToCanvas_x(ms.cur_pos_x) > left && EscapeRoom.windowToCanvas_x(ms.cur_pos_x) < right && EscapeRoom.windowToCanvas_y(ms.cur_pos_y) > high && EscapeRoom.windowToCanvas_y(ms.cur_pos_y) < low;

}

keypad::keypad(Game& mygame)
	:GameObject(mygame)
{
	this->password = password;
}

keypad::~keypad()
{
}
