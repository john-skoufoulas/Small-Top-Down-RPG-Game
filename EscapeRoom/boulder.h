#pragma once
#include "GameObject.h"

class boulder : public GameObject {
public:
	boulder(class Game& mygame);
	void update() override;
	void draw() override;
};
