#pragma once
#include "GameObject.h"
#include "iostream"

class Game;

class Player : public GameObject {
protected:
	int static const default_speed = 15;
	float speed = 0;
	bool moving_up = false;
	bool moving_down = false;
	bool moving_left = false;
	bool moving_right = false;
	int up_next;
	int right_next;
	int down_next;
	int left_next;
	bool stop_movement = false;
	std::string direction = "front";
	float tmp = 0.0f;
public:
	Player(class Game& mygame);
	~Player();
	void setTileX(int tile);
	void setTileY(int tile);
	int getTileX();
	int getTileY();
	float getPosX();
	float getPosY();
	bool isMoving();
	void set_stop_movement(bool stop);
	std::string getDirection();
	int watching_tile_x();
	int watching_tile_y();
	void update() override;
	void draw() override;
};
