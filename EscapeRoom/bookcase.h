#pragma once
#include "Movable_Object.h"

class bookcase : public Movable_Object {
public:
	bookcase(class Game& mygame);
	void update() override;
	void draw() override;
}; 