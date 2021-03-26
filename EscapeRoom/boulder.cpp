#include "boulder.h"
#include "Game.h"

void boulder::update()
{
}

void boulder::draw()
{
	graphics::Brush br;
	br.texture = "assets\\boulder.png";
	br.outline_opacity = 0;
	graphics::drawRect(pos_x, pos_y, TILE, TILE, br);
}

boulder::boulder(Game& mygame)
	:GameObject(mygame)
{
}
