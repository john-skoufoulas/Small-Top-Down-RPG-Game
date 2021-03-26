#pragma once
#include "graphics.h"
#include "Map.h"
#include "bookcase.h"
#include "boulder.h"
#include "Player.h"
#include "hammer_part.h"
#include "keypad.h"
#include "StartScreen.h"
#include "EndScreen.h"

class Game {
	unsigned int window_w = WINDOW;
	unsigned int window_h = WINDOW;
	Player* player = nullptr;
	int Active_Map;
	Map* map0 = nullptr;
	Map* map1 = nullptr;
	Map* map2 = nullptr;
	bookcase* bookcase01 = nullptr;
	boulder* boulder11 = nullptr;
	hammer_part* hammer[3];
	keypad* keypad01 = nullptr;
	StartScreen* myStartScreen = nullptr;
	EndScreen* myEndScreen = nullptr;
	bool map0_solved = false;
	bool map1_solved = false;
	bool hammer_found[3] = {false , false, false};
	bool Master_Key_found = false;
	bool pause = false;
	bool riddle01 = false;
	bool riddle02 = false;
	bool transition0 = false;
	bool transition1 = false;
	bool transition2 = false;
	bool destruction_order = false;
	bool endScreen = false;
public :
	bool getDestruction_order();
	//Window x,y adjustments-----
	unsigned int getWindow_w() { return window_w; }
	unsigned int getWindow_h() { return window_h; }
	void setWindow_x_y(unsigned int w, unsigned int h) { window_w = w; window_h = h; }
	float windowToCanvas_x(float x);
	float windowToCanvas_y(float y);
	//------Window x,y adjustments
	void message_init(std::string s, int row);
	void message();
	int getActiveMap();
	bool getHammerFound(int i);
	int getMapTile(int i, int j);
	int player_watching();
	void update();
	void draw();
	void init();
	void generateMaps();
	void resetGame();
	Game();
	~Game();
};