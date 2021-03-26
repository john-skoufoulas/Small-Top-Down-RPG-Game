#pragma once
#include "iostream"
#include "graphics.h"
#include "config.h"
class Credits {
	float pos_y = 420;
public:
	void update();
	void draw();
	void printInCenter(std::string note, int row, int size);
	Credits();
	~Credits();
};