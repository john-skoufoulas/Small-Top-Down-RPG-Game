#pragma once
#include "GameObject.h"

class Movable_Object : public GameObject {
protected:
	float speed = 10.0f;
	bool move = false;
	int start_x;
	int start_y;
public:
	Movable_Object(class Game& mygame);
	int getStartX();
	int getStartY();
	void setMove(bool m);
	virtual void update() = 0;
	virtual void draw() = 0;
	void init(float x, float y) ;
};