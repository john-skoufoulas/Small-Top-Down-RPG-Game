#include "Movable_Object.h"
#include "Game.h"

int Movable_Object::getStartX()
{
	return start_x;
}

int Movable_Object::getStartY()
{
	return start_y;
}

void Movable_Object::setMove(bool m)
{
	this->move = m;
}

void Movable_Object::init(float x, float y)
{
	this->pos_x = x;
	this->pos_y = y;
	this->start_x = x;
	this->start_y = y;
}
Movable_Object::Movable_Object(Game& mygame) 
	:GameObject(mygame)
{
}


