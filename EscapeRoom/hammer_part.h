#pragma once
#include "Movable_Object.h"

class hammer_part : public Movable_Object {
	std::string part;
public:
	void update() override;
	void draw() override;
	hammer_part(class Game& mygame, std::string part);
};