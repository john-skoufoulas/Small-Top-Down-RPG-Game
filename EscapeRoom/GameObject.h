#pragma once
#include "graphics.h"
#include "config.h"


class GameObject {
protected:
	class Game &EscapeRoom;
	float pos_x;
	float pos_y;
public:
	virtual void update() = 0;
	virtual void draw() = 0;
	void init(float x, float y);
	GameObject(class Game& mygame);
};