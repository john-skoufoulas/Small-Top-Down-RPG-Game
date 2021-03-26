#include "GameObject.h"
#include "Game.h"

void GameObject::draw()
{
}

GameObject::GameObject(Game& mygame)
	: EscapeRoom(mygame)
{
}
void GameObject::init(float x, float y)
{
	this->pos_x = x;
	this->pos_y = y;
}
