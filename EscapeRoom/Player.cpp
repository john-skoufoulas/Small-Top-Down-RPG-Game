#include "Player.h"
#include "Game.h"

void Player::update()
{
	if(!stop_movement){
		if (graphics::getKeyState(graphics::SCANCODE_LSHIFT)) {
			this->speed = 27.0f;
		}
		else this->speed = default_speed;

		//  UP  _____________
		if (graphics::getKeyState(graphics::SCANCODE_W) && !moving_up && !moving_right && !moving_down && !moving_left && EscapeRoom.getMapTile(getTileX(), getTileY() - 1) == 0) {
			tmp = pos_y;
			moving_up = true;
		}
		if (moving_up) {
			pos_y -= speed * graphics::getDeltaTime() / 150;
			if (tmp - pos_y <= TILE / 4) this->direction = "back1";
			else if (tmp - pos_y < TILE / 2) this->direction = "back";
			else if (tmp - pos_y < TILE / 1) this->direction = "back2";
			else  this->direction = "back";
			if (tmp - pos_y >= TILE) {
				pos_y = tmp - TILE;
				moving_up = false;
			}
		}

		//  RIGHT  _____________
		if (graphics::getKeyState(graphics::SCANCODE_D) && !moving_up && !moving_right && !moving_down && !moving_left && EscapeRoom.getMapTile(getTileX() + 1, getTileY() ) == 0) {
			tmp = pos_x;
			moving_right = true;
		}
		if (moving_right) {
			pos_x += speed * graphics::getDeltaTime() / 150;
			if (pos_x - tmp <= TILE / 4) this->direction = "right1";
			else if (pos_x - tmp < TILE / 2) this->direction = "right";
			else if (pos_x - tmp < TILE / 1) this->direction = "right2";
			else  this->direction = "right";
			if (pos_x - tmp >= TILE) {
				pos_x = tmp + TILE;
				moving_right = false;
			}
		}

		//  DOWN  _____________
		if (graphics::getKeyState(graphics::SCANCODE_S) && !moving_up && !moving_right && !moving_down && !moving_left && EscapeRoom.getMapTile(getTileX(), getTileY() + 1) == 0)  {
			tmp = pos_y;
			moving_down = true;
		}
		if (moving_down) {
			pos_y += speed * graphics::getDeltaTime() / 150;
			if (pos_y - tmp <= TILE / 4) this->direction = "front1";
			else if (pos_y - tmp < TILE / 2) this->direction = "front";
			else if (pos_y - tmp < TILE / 1) this->direction = "front2";
			else  this->direction = "front";
			if (pos_y - tmp >= TILE) {
				pos_y = tmp + TILE;
				moving_down = false;
			}
		}

		//  LEFT  _____________
		if (graphics::getKeyState(graphics::SCANCODE_A) && !moving_up && !moving_right && !moving_down && !moving_left && EscapeRoom.getMapTile(getTileX() - 1, getTileY()) == 0) {
			tmp = pos_x;
			moving_left = true;
		}
		if (moving_left) {
			pos_x -= speed * graphics::getDeltaTime() / 150;
			if (tmp - pos_x <= TILE / 4) this->direction = "left1";
			else if (tmp - pos_x < TILE / 2) this->direction = "left";
			else if (tmp - pos_x < TILE / 1) this->direction = "left2";
			else  this->direction = "left";
			if (tmp - pos_x >= TILE) {
				pos_x = tmp - TILE;
				moving_left = false;
			}
		}
		//Facing direction when stil_____________________
		if (!isMoving()) {
			if (graphics::getKeyState(graphics::SCANCODE_W)) this->direction = "back";
			if (graphics::getKeyState(graphics::SCANCODE_S)) this->direction = "front";
			if (graphics::getKeyState(graphics::SCANCODE_D)) this->direction = "right";
			if (graphics::getKeyState(graphics::SCANCODE_A)) this->direction = "left";
		}
	}
 }

void Player::draw()
{
	graphics::Brush br;
	br.texture = "assets\\character_assets\\character_" + direction + ".png";
	br.outline_opacity = 0;
	graphics::drawRect(pos_x, pos_y, TILE, TILE, br);
}
//--------------------------------------

std::string Player::getDirection()
{
	return this->direction;
}


//--------------------------------------
int Player::getTileX()
{
	return (pos_x - 0.5 * TILE) / TILE;
}

int Player::getTileY()
{
	return (pos_y - 0.5 * TILE) / TILE;
}
//--------------------------------------
float Player::getPosX()
{
	return this->pos_x;
}

float Player::getPosY()
{
	return this->pos_y;
}


int Player::watching_tile_x()
{
	if (!isMoving()) {
		if (this->direction == "back") {
			return this->getTileX();
		}
		else if (this->direction == "front") {
			return this->getTileX();
		}
		else if (this->direction == "right") {
			return this->getTileX() + 1;
		}
		else {
			return this->getTileX() - 1;
		}
	}
	else {
		return getTileX();
	}
}

int Player::watching_tile_y()
{
	if (!isMoving()) {
		if (this->direction == "back") {
			return this->getTileY() - 1;
		}
		else if (this->direction == "front") {
			return this->getTileY() + 1;
		}
		else if (this->direction == "right") {
			return this->getTileY();
		}
		else {
			return this->getTileY();
		}
	}
	else {
		return getTileY();
	}
}

Player::Player(Game& mygame)
	:GameObject(mygame)
{
	up_next = 1;
	right_next = 0;
	down_next = 0; 
	left_next = 1;
}
//--------------------------------------
void Player::setTileX(int tile)
{
	this->pos_x = (tile + 0.5) * TILE ;
}

void Player::setTileY(int tile)
{
	this->pos_y = (tile + 0.5) * TILE;
}

Player::~Player()
{
}

bool Player::isMoving()
{
	return moving_up || moving_down || moving_left || moving_right;
}

void Player::set_stop_movement(bool stop)
{
	this->stop_movement = stop;
}
