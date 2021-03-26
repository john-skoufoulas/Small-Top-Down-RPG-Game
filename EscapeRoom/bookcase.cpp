#include "bookcase.h"
#include "Game.h"

bookcase::bookcase(Game& mygame)
	:Movable_Object(mygame)
{
}

void bookcase::update()
{
	if (move) {
		pos_x += speed * graphics::getDeltaTime() / 250;
	}
	if (pos_x >= start_x + TILE) {
		pos_x = start_x + TILE;
		move = false;
	}
}

void bookcase::draw()
{
	graphics::Brush br;
	br.texture = "assets\\bookcase.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x + 1, pos_y - TILE, 2* TILE, 2 * TILE, br);
}
