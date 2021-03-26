#include "hammer_part.h"
#include "Game.h"

void hammer_part::update()
{
	if (EscapeRoom.getHammerFound(0) && EscapeRoom.getHammerFound(1) && EscapeRoom.getHammerFound(2) && !move){
		move = true;
	}
	if (move) {
		pos_x += speed * graphics::getDeltaTime() / 250;
	}
	if (pos_x >= CANVAS - 0.5 * TILE) pos_x = CANVAS - 0.5 * TILE;
}

void hammer_part::draw()
{
	graphics::Brush br;
	br.texture = "assets\\"+ part +".png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, TILE, TILE, br);
}

hammer_part::hammer_part(Game& mygame, std::string part)
	:Movable_Object(mygame)
{
	this->part = part;
	if (this->part == "hammer_handle") {
		this->speed = 5.0f;
	}
	if (this->part == "hammer_body") {
		this->speed = 10.0f;
	}
	if (this->part == "hammer_head") {
		this->speed = 15.0f;
	}
	
}
