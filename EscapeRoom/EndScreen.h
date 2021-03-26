#pragma once
#include "graphics.h"
#include "config.h"
#include "Credits.h"

class EndScreen {
	bool goToStartScreen = false;
	float rot = 180.0f;
	float x = 0;
	float op = 0;
	float time = -1;
public:
	bool getGoToStartScreen();
	void update();
	void draw();
	EndScreen();
	~EndScreen();
};
