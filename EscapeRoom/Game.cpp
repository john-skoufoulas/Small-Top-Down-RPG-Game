#include "Game.h"
#include "iostream"
#include "vector"

//#define DEBUG ;

void Game::update()
{	
	//Close Window_____________________________________!
	if (myStartScreen && myStartScreen->getExit()) destruction_order = true;

	if (graphics::getKeyState(graphics::SCANCODE_P)) pause = true;
	if (graphics::getKeyState(graphics::SCANCODE_O)) pause = false;

	//EndScreen_______________________________________
	if (myEndScreen) {
		pause = true;
		myEndScreen->update();
		if (myEndScreen->getGoToStartScreen()) {
			delete myEndScreen;
			myEndScreen = nullptr;
			myStartScreen = new StartScreen(*this);
			graphics::playMusic("assets\\main_menu_music.mp3", 0.3f, true, 1000);
			resetGame();
		}
	}
	//StartScreen_______________________________________
	if (myStartScreen) {
		pause = true;
		myStartScreen->update();
		if (myStartScreen->getgameStart()) {
			graphics::stopMusic(1500);
			delete myStartScreen;
			myStartScreen = nullptr;
			pause = false;
			graphics::playMusic("assets\\game_music.mp3", 0.3f, true, 3000);
		}
	}

	if (!pause) {
		//Player creation and update_____________________
		if (!player) {
			player = new Player(*this);
			player->init(3.5 * TILE, 3.5 * TILE);
			if (player) player->set_stop_movement(true);
		}
		if (player) {
			player->update();
		}
		if (transition1  && graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			player->set_stop_movement(false);
			transition1 = false;
		}
		if (transition2 && graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			player->set_stop_movement(false);
			transition2 = false;
		}
		if (transition0 && graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			player->set_stop_movement(false);
			transition0 = false;
		}
		//Active Map Update______________________________
		if (Active_Map == 0) {
			bookcase01->update();
			if (!keypad01 && !riddle02 && player_watching() == 7 && graphics::getKeyState(graphics::SCANCODE_C)) {
				this->keypad01 = new keypad(*this);
				player->set_stop_movement(true);
			}
			if (keypad01 && keypad01->getInput().length() >= 4) {
				if (keypad01->getInput() == "4238") {
					riddle02 = true;
				}
				delete keypad01;
				keypad01 = nullptr;
				player->set_stop_movement(false);
			}
			if (riddle02 && !map0_solved) {
				map0_solved = true;
				graphics::playSound("assets\\boost.wav", 0.1f, false);
				bookcase01->setMove(true);
				map0->updateMap(4, 2, 0);
				map0->updateMap(6, 2, 2);
			}
			if (!riddle01 && player_watching() == 13 && graphics::getKeyState(graphics::SCANCODE_SPACE)) {
				map0->updateMap(8, 8, 13);
				riddle01 = true;
			}
			if (Master_Key_found && !myEndScreen && player_watching() == 10 && graphics::getKeyState(graphics::SCANCODE_SPACE)) {
				graphics::playSound("assets\\door_open.mp3", 0.2f, false);
				myEndScreen = new EndScreen();
				resetGame();
				pause = true;
			}
		}
		if (Active_Map == 1) {
			if (!map1_solved && player_watching() == 21 && graphics::getKeyState(graphics::SCANCODE_SPACE) && hammer_found[0] && hammer_found[1] && hammer_found[2]) {
				graphics::playSound("assets\\boulder_smash.mp3", 0.15f, false);
				map1_solved = true;
			}

			if (map1_solved && boulder11) {
				delete boulder11;
				boulder11 = nullptr;
				map1->updateMap(5, 4, 0);
			}

			if (!Master_Key_found && player_watching() == 12 && graphics::getKeyState(graphics::SCANCODE_SPACE)) {
				Master_Key_found = true;
				graphics::playSound("assets\\key.mp3", 0.2f, false);
			}
		}

		if (Active_Map == 2) {
			if ((player_watching() == 17 && graphics::getKeyState(graphics::SCANCODE_SPACE) && !hammer_found[0]) || graphics::getKeyState(graphics::SCANCODE_B)) {
				hammer_found[0] = true;
			}
			if ((player_watching() == 18 && graphics::getKeyState(graphics::SCANCODE_SPACE) && !hammer_found[1]) || graphics::getKeyState(graphics::SCANCODE_B)) {
				hammer_found[1] = true;
			}
			if ((player_watching() == 19 && graphics::getKeyState(graphics::SCANCODE_SPACE) && !hammer_found[2]) || graphics::getKeyState(graphics::SCANCODE_B)) {
				hammer_found[2] = true;
			}
		}
		
		//Travel from Map to Map________________________
		if (Active_Map == 0 && player->getPosX() == 4.5 * TILE && player->getPosY() == 1.5 * TILE) {
			Active_Map = 1;
			player->setTileX(7);
			player->setTileY(13);
			transition1 = true;
			player->set_stop_movement(true);
		}

		if (Active_Map == 1 && player->getPosX() == 7.5 * TILE && player->getPosY() == 14.5 * TILE) {
			Active_Map = 0;
			player->setTileX(4);
			player->setTileY(2);
		}

		if (Active_Map == 1 && player->getPosX() == 14.5 * TILE && player->getPosY() == 2.5 * TILE) {
			Active_Map = 2;
			player->setTileX(1);
			player->setTileY(7);
			transition2 = true;
			player->set_stop_movement(true);
		}
		if (Active_Map == 2 && player->getPosX() == 0.5 * TILE && player->getPosY() == 7.5 * TILE) {
			Active_Map = 1;
			player->setTileX(13);
			player->setTileY(2);
		}

		//Hammer Update_______________________
		hammer[0]->update();
		hammer[1]->update();
		hammer[2]->update();
		if (keypad01) {
			keypad01->update();
		}
	}
	else if (!myEndScreen && !myStartScreen){
		if (graphics::getKeyState(graphics::SCANCODE_M)) {
			resetGame();
			myStartScreen = new StartScreen(*this);
			graphics::playMusic("assets\\main_menu_music.mp3", 0.3f, true, 1000);
		}
		if (graphics::getKeyState(graphics::SCANCODE_E)) {
			destruction_order = true;
		}
	}
}

void Game::draw()
{
	//Draw Maps and Player
	if (Active_Map == 0) {
		map0->draw();
		bookcase01->draw();
		if (riddle01) {
			graphics::Brush br;
			br.texture = "assets\\password.png";
			br.outline_opacity = 0;
			br.fill_opacity = 1;
			graphics::drawRect(8.5 * TILE, 8.5 * TILE - 5, TILE, 2 * TILE, br);
		}
	}

	if (Active_Map == 1) {
		map1->draw();
		if (map1_solved) {
			graphics::Brush br;
			br.texture = "assets\\hiddenPath.png";
			br.outline_opacity = 0;
			graphics::drawRect(CANVAS / 4 - 8.7, CANVAS / 2, CANVAS / 2 - 16, CANVAS, br);
		}

		if (!Master_Key_found) {
			graphics::Brush br;
			br.texture = "assets\\Master_Key.png";
			br.fill_opacity = 1.0f;
			br.outline_opacity = 0;
			graphics::drawRect(5.5 * TILE, 9.5 * TILE, TILE, TILE, br);
		}

		if (!map1_solved && boulder11) {
			boulder11->draw();
		}
	}

	if (Active_Map == 2) {
		map2->draw();
	}

	if (player) player->draw();

	if (Active_Map == 2) {
		graphics::Brush br;
		br.outline_opacity = 0;
		br.texture = "assets\\map2_trees.png";
		graphics::drawRect(CANVAS / 2 , CANVAS / 2 + 8 , 452, 468, br);
	}
	//Keypad_______________________________
	if (keypad01) keypad01->draw();
	//Top Right itembar____________________________
	graphics::Brush br;
	br.outline_opacity = 0;
	br.fill_opacity = 0.9f;
	br.fill_color[0] = 0.2f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	graphics::drawRect(CANVAS - 2 * TILE, TILE / 2, 4 * TILE, TILE, br);
	graphics::drawSector(CANVAS - 4 * TILE, 0, 0, TILE, 180, 270, br);
	//Hammer and Master-Key on itembar____________________________
	if (hammer_found[0]) {
		hammer[0]->draw();
	}
	if (hammer_found[1]) {
		hammer[1]->draw();
	}
	if (hammer_found[2]) {
		hammer[2]->draw();
	}
	if (Master_Key_found) {
		graphics::Brush br;
		br.texture = "assets\\Master_Key.png";
		br.outline_opacity = 0;
		graphics::drawRect(CANVAS - 2.5 * TILE, 0.5 * TILE, TILE, TILE, br);
	}
	//PAUSE sidebar______________________________
	if (pause && !myStartScreen && !myEndScreen) {
		br.fill_opacity = 0.7f;
		br.texture = "";
		br.fill_color[0] = 0.0f;
		br.fill_color[1] = 0.0f;
		br.fill_color[2] = 0.0f;
		br.outline_opacity = 0.0f;
		graphics::drawRect(0, CANVAS / 2,CANVAS / 1.2, CANVAS, br);

		br.fill_color[0] = 0.9f;
		br.fill_color[1] = 0.9f;
		br.fill_color[2] = 0.9f;
		graphics::setFont("assets\\newGame.ttf");
		graphics::drawText(28, 80, 17, "Main  Menu  (M)", br);

		graphics::drawText(30, 160, 16, "Exit  (E)", br);
	}

	//DEBUG print ______________________________
	#ifdef DEBUG

	if (player) {
		graphics::Brush br;

		graphics::setFont("assets\\myFont.ttf");
		char info[100];
		sprintf_s(info,"( %d, %d)", player_watching() , player->getTileX(), player->getTileY());
		graphics::drawText(15,25,30,info,br); 

		br.outline_opacity = 0;
		br.texture = "assets\\mapGrid.png";
		graphics::drawRect(CANVAS / 2, CANVAS / 2, CANVAS, CANVAS, br);

	}
	#endif
	message();

	if (myStartScreen) {
		myStartScreen->draw();
	}

	if (myEndScreen) {
		myEndScreen->draw();
	}
}

int Game::getActiveMap()
{
	return Active_Map;
}

int Game::getMapTile(int i, int j)
{
	if (Active_Map == 0)
		return map0->getGridTile(i, j);

	if (Active_Map == 1)
		return map1->getGridTile(i, j);

	if (Active_Map == 2)
		return map2->getGridTile(i, j);
}

int Game::player_watching() {
	if (Active_Map == 0)
		return map0->getGridTile(player->watching_tile_x(), player->watching_tile_y());
	else if (Active_Map == 1)
		return map1->getGridTile(player->watching_tile_x(), player->watching_tile_y());
	else
		return map2->getGridTile(player->watching_tile_x(), player->watching_tile_y());
}

bool Game::getHammerFound(int i)
{
	return hammer_found[i];
}

void Game::init()
{
	graphics::playMusic("assets\\main_menu_music.mp3",0.3f,true,1000);

}
void Game::message_init(std::string s, int row) {
	graphics::Brush br;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.outline_color[0] = 0.75f;
	br.outline_color[0] = 0.75f;
	br.outline_color[0] = 0.75f;
	br.outline_color[0] = 0.75f;
	br.outline_opacity = 0.4f;
	graphics::drawRect(CANVAS / 2, CANVAS * 0.89f , CANVAS * 0.9f, 3 * TILE,br);
	br.fill_color[0] = 0.75f;
	br.fill_color[1] = 0.75f;
	br.fill_color[2] = 0.75f;
	graphics::setFont("assets\\message_font.ttf");
	graphics::drawText(CANVAS * 0.1f - 8, CANVAS * 0.84f + row * 22, 18, s, br);
}
void Game::message() 
{
	if (player) {
		//Interactions___________________________________
		if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
			if (player_watching() == 2) {
				message_init("This bookcase isn't very useful.", 0);
			}
			if (player_watching() == 3) {
				message_init("Hi Bob, you are probably wondering what is going on.", 0);
				message_init("We took your phone so you can't call the police and ruin", 1);
				message_init("the surprise... haha just kidding...", 2);
				message_init("Anyway, i suggest you start looking for clues and get out.", 3);
			}
			if (player_watching() == 4) {
				message_init("Breaking news: Explosion Wensday is now a thing", 0);
			}
			if (player_watching() == 5) {
				message_init("I'm trying as hard as I can but I can't poop!", 0);
			}
			if (player_watching() == 6) {
				message_init("I probably need to wash those..... Eh, I 'll do it later", 0);
			}
			if (player_watching() == 7) {
				message_init("Looks like a old computer. On the screen it says: ", 0);
				message_init("''Type a 4 digit code'' .(To insert code press c)", 1);
				message_init("I wonder if i can play Warframe on it...", 2);
			}
			if (player_watching() == 8) {
				message_init("Jesus christ, Why is my head on the mirror so BIG!?!", 0);
			}
			if (player_watching() == 9) {
				message_init("My bed looks comfy, too bad I dont have time to sleep.", 0);
				message_init("I have to find out whats going on.", 1);
			}
			if (player_watching() == 10) {
				message_init("No luck, the main door is locked. Maybe i need to find", 0);
				message_init("a KEY.", 1);
			}
			if (player_watching() == 11) {
				message_init("This boulder is too heavy to move by myself.", 0);
			}
			if (player_watching() == 13) {
				message_init("4 2 3 8 !", 0);
			}
			if (player_watching() == 14) {
				message_init("Good job finding, the ''Tangled Forest''! Witch is", 0);
				message_init("a regular forest, exept there is a MAZE in it!!", 1);
				message_init("Boom big reveal. Now you have to wonder inside the maze", 2);
				message_init("and try to find 3 peaces of something you need.", 3);
				graphics::Brush br;
				br.texture = "assets\\maze.png";
				br.outline_opacity = 0;
				br.fill_opacity = 0.7f;
				graphics::drawRect(CANVAS / 2, CANVAS / 2 , 250, 250, br);
			}
			if (player_watching() == 15) {
				message_init("Wait...what is that in there?!... Its a note!", 0);
				message_init("''The answer is in the walls.''", 1);
			}
			if (player_watching() == 16) {
				message_init("This box is Empty.", 0);
			}
			if (player_watching() == 20) {
				message_init("Uh, there is the Master Key. Its so close....", 0);
				message_init("but i cant reach it. I have to find another way in.", 1);
			}
			if (player_watching() == 21) {
				message_init("This boulder is too heavy to break by myself.", 0);
			}
		}
		//Transitions_________________________________
		if (transition0 && !myStartScreen && !myEndScreen) {
			message_init("*Weaks up* Hmm, somehting feels strange. My phone is ", 0);
			message_init("missing and I dont remember leaving this note on my ", 1);
			message_init("desk. Maybe i should investigate.", 2);
		}
		if (transition1) {
			message_init("Wow , there is a cave next to my appartment!", 0);
		}
		if (transition2) {
			message_init("Wow , there is a forest next to my appartment.", 0);
			message_init("This is getting a bit old...", 1);
		}

	}
}

void Game::generateMaps()
{	//Map Grid Meaning: 
	// 0) Walkable Area
	// 1) Non functional terrain
	// 2) bookcase
	// 3) Instructions note 1
	// 4) TV
	// 5) Toilet
	// 6) Loundry
	// 7) Code insert
	// 8) Mirror
	// 9) Bed
	// 10) Exit
	// 11) boulder
	// 12) Master Key
	// 13) writing in the wall
	// 14) Instructions note 2
	// 15) Washing machine
	// 16) Empty box 
	// 17) hammer part 1 box 
	// 18) hammer part 2 box 
	// 19) hammer part 3 box 
	// 20) Unreachable key
	// 21) Breakable boulder

	std::vector<std::vector<int>> m0
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,0,1,1,1,1,1,1,1,1,1,1},
		{1,9,9,1,2,2,0,1,15,6,8,8,0,5,1},
		{1,9,9,0,0,0,0,1,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,3,1,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,1,1,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,1,0,0,0,0,0,1,1},
		{1,1,1,1,0,0,0,1,1,1,0,1,1,1,1},
		{1,1,1,1,1,0,0,1,13,1,0,1,1,1,1},
		{1,1,1,1,1,0,0,0,0,0,0,2,2,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
		{1,0,0,0,0,0,0,0,7,0,0,0,0,1,1},
		{1,1,4,4,4,1,1,1,1,1,1,10,10,1,1}
	};

	map0 = new Map("map0.png", m0);
	std::vector<std::vector<int>>().swap(m0);
	Active_Map = 0;
	bookcase01 = new bookcase(*this);
	bookcase01->init(5 * TILE, 3 * TILE);

	std::vector<std::vector<int>> m1
	{
		{1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,0,0,0,0,11,1,1,1,1,1},
		{1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
		{1,1,1,1,1,16,0,0,0,0,1,1,1,1,1},
		{1,1,0,0,0,21,0,0,0,0,1,1,1,1,1},
		{1,1,0,1,1,0,16,0,0,0,1,1,1,1,1},
		{1,1,0,1,1,16,16,0,0,0,1,1,1,1,1},
		{1,1,0,1,1,0,0,0,0,0,1,1,1,1,1},
		{1,1,0,1,1,20,1,0,0,0,0,1,1,1,1},
		{1,1,0,1,1,12,20,0,0,0,1,1,1,1,1},
		{1,1,0,0,0,0,1,0,0,0,1,1,1,1,1},
		{1,1,1,1,1,1,1,0,0,16,1,1,1,1,1},
		{1,1,1,1,1,0,0,0,0,16,1,1,1,1,1},
		{1,1,1,1,0,0,0,0,0,16,1,1,1,1,1},
		{1,1,1,1,1,1,1,0,1,1,1,1,1,1,1}
	};
	map1 = new Map("map1.png", m1);
	std::vector<std::vector<int>>().swap(m1);
	boulder11 = new boulder(*this);
	boulder11->init(5.5 * TILE, 4.5 * TILE);

	std::vector<std::vector<int>> m2
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,0,0,0,1,0,0,0,0,0,0,0,1,1},
		{1,1,0,1,0,1,0,1,1,1,1,1,0,1,1},
		{1,1,0,1,0,0,0,1,17,0,0,0,0,1,1},
		{1,1,0,1,1,1,1,1,1,1,1,1,0,1,1},
		{1,14,0,0,0,0,0,1,20,1,0,0,0,1,1},
		{0,0,0,1,1,1,0,1,0,1,0,1,1,1,1},
		{1,1,0,0,0,0,0,1,0,1,0,0,0,1,1},
		{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1},
		{1,1,0,0,0,1,0,0,0,0,0,1,1,1,1},
		{1,1,0,1,0,0,0,0,1,1,0,0,0,1,1},
		{1,1,18,1,0,1,1,0,0,1,0,1,19,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} 
	};
	map2 = new Map("map2.png", m2);
	std::vector<std::vector<int>>().swap(m2);
}

float Game::windowToCanvas_x(float x)
{
	if (getWindow_w() > CANVAS) {
		return (x - 330) * 0.68f;
	}
	else return x;
}

float Game::windowToCanvas_y(float y)
{
	if (getWindow_w() > CANVAS) {
		return y* 0.68f;
	}
	else return y;
}

Game::Game()
{
	myStartScreen = new StartScreen(*this);
	generateMaps();

	hammer[0] = new hammer_part(*this, "hammer_head");
	hammer[0]->init(CANVAS - 3.5 * TILE, 0.5 * TILE);
	hammer[1] = new hammer_part(*this, "hammer_body");
	hammer[1]->init(CANVAS - 2.5 * TILE, 0.5 * TILE);
	hammer[2] = new hammer_part(*this, "hammer_handle");
	hammer[2]->init(CANVAS - 1.5 * TILE, 0.5 * TILE);

	transition0 = true;
}

bool Game::getDestruction_order()
{
	return this->destruction_order;
}

void Game::resetGame() {

	Active_Map = 0;
	map0_solved = false;
	map1_solved = false;
	delete bookcase01;
	bookcase01 = nullptr;
	bookcase01 = new bookcase(*this);
	bookcase01->init(5 * TILE, 3 * TILE);
	map0->updateMap(4, 2, 2);
	map0->updateMap(6, 2, 0);
	player->setTileX(3);
	player->setTileY(3);
	player->set_stop_movement(true);
	riddle01 = false;
	riddle02 = false;
	if (!boulder11) {
		boulder11 = new boulder(*this);
		boulder11->init(5.5 * TILE, 4.5 * TILE);
	}
	map1->updateMap(5, 4, 11);
	delete hammer[2];
	hammer[2] = nullptr;
	delete hammer[1];
	hammer[1] = nullptr;
	delete hammer[0];
	hammer[0] = nullptr;
	hammer_found[0] = false;
	hammer_found[1] = false;
	hammer_found[2] = false;
	hammer[0] = new hammer_part(*this, "hammer_head");
	hammer[0]->init(CANVAS - 3.5 * TILE, 0.5 * TILE);
	hammer[1] = new hammer_part(*this, "hammer_body");
	hammer[1]->init(CANVAS - 2.5 * TILE, 0.5 * TILE);
	hammer[2] = new hammer_part(*this, "hammer_handle");
	hammer[2]->init(CANVAS - 1.5 * TILE, 0.5 * TILE);
	Master_Key_found = false;
	if (map1_solved) {
		map1->updateMap(5, 4, 1);
	}
	transition0 = true;
	transition1 = false;
	transition2 = false;
}

Game::~Game()
{
	delete player;
	player = nullptr;
	delete map0;
	map0 = nullptr;
	delete map1;
	map1 = nullptr;
	delete map2;
	map2 = nullptr;
	delete bookcase01;
	bookcase01 = nullptr;
	if (boulder11) {
		delete boulder11;
		boulder11 = nullptr;
	}
	delete hammer[2];
	hammer[2] = nullptr;
	delete hammer[1];
	hammer[1] = nullptr;
	delete hammer[0];
	hammer[0] = nullptr;
	if (keypad01) {
		delete keypad01;
		keypad01 = nullptr;
	}
	delete myStartScreen;
	myStartScreen = nullptr;
}
