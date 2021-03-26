#include "StartScreen.h"
#include "Game.h"

void StartScreen::update()
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	if (myCredits) {
		myCredits->update();
	}
	if (!show_credits) {
		if (myCredits) {
			delete myCredits;
			myCredits = nullptr;
		}
		//Start Button press__________________________
		if (ms.button_left_down && cursor_loc(183, 200, 373, 110)) {
			start_button_down = true;
		}
		else {
			start_button_down = false;
		}
		if (ms.button_left_released) {
			if (cursor_loc(183, 200, 373, 110)){
				this->gameStart = true;
			}
		}

		//Controls press__________________________
		if (ms.button_left_down && cursor_loc(251, 268, 320, 166)) {
			controls_button_down = true;
		}
		else {
			controls_button_down = false;
		}
		if (ms.button_left_released) {
			if (cursor_loc(251, 268, 320, 166)) {
				this->show_controls = true;
			}
		}

		//Credits press__________________________
		if (ms.button_left_down && cursor_loc(320, 340, 297, 183)) {
			credits_button_down = true;
		}
		else {
			credits_button_down = false;
		}
		if (ms.button_left_released) {
			if (cursor_loc(320, 340, 297, 183)) {
				this->show_credits = true;
			}
		}

		//Exit press__________________________
		if (ms.button_left_down && cursor_loc(392, 410, 272, 211)) {
			exit_button_down = true;
		}
		else {
			exit_button_down = false;
		}
		if (ms.button_left_released) {
			if (cursor_loc(392, 410, 272, 211)) {
				exit = true;
			}
		}
	}
	else if (show_credits){
		if (!myCredits) {
			myCredits = new Credits();
		}
		if (ms.button_left_released && cursor_loc(423, 439, 129, 50) && show_credits) {
			this->show_credits = false;
		}
	}
	if (show_controls && cursor_loc(423, 439, 129, 50) && ms.button_left_released){
		this->show_controls = false;
	}
	//Back button interaction
	if (ms.button_left_down && cursor_loc(423, 439, 129, 50)) {
		back_button_down = true;
	}
	else {
		back_button_down = false;
	}
}

void StartScreen::draw()
{
	graphics::Brush br;
	if (!show_credits && !show_controls ) {
		br.outline_opacity = 0;
		br.texture = "assets\\start_screen.png";
		graphics::drawRect(CANVAS / 2, CANVAS / 2, CANVAS, CANVAS, br);

		graphics::setFont("assets\\newGame.ttf");

		//Game Start Button____________________________________
		if (start_button_down) {
			br.fill_color[0] = 0.85f;
			br.fill_color[1] = 0.85f;
			br.fill_color[2] = 0.85f;
		}
		else {
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
		}
		graphics::drawText(110, 200, 23, "Start  new  Game", br);

		//Controls Button____________________________________
		if (controls_button_down) {
			br.fill_color[0] = 0.85f;
			br.fill_color[1] = 0.85f;
			br.fill_color[2] = 0.85f;
		}
		else {
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
		}
		graphics::drawText(167, 268, 23, "Controls", br);

		//Credits Button____________________________________
		if (credits_button_down) {
			br.fill_color[0] = 0.85f;
			br.fill_color[1] = 0.85f;
			br.fill_color[2] = 0.85f;
		}
		else {
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
		}
		graphics::drawText(183, 338, 23, "Credits", br);

		//Exit Button______________________________________
		if (exit_button_down) {
			br.fill_color[0] = 0.85f;
			br.fill_color[1] = 0.85f;
			br.fill_color[2] = 0.85f;
		}
		else {
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
		}
		graphics::drawText(212, 405, 23, "Exit", br);
	}
	else if (show_credits){

		if (myCredits) {
			myCredits->draw();
		}
		//Credits Back button______________________________________
		if (back_button_down) {
			br.fill_color[0] = 0.85f;
			br.fill_color[1] = 0.85f;
			br.fill_color[2] = 0.85f;
		}
		else {
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
		}
		graphics::drawText(50, 440, 23, "back", br);
	}
	else if (show_controls) {
		br.outline_opacity = 0.0f;
		br.texture = "assets\\start_screen.png";
		graphics::drawRect(CANVAS / 2, CANVAS / 2, CANVAS, CANVAS, br);
		//Controls Back button______________________________________
		if (back_button_down) {
			br.fill_color[0] = 0.85f;
			br.fill_color[1] = 0.85f;
			br.fill_color[2] = 0.85f;
		}
		else {
			br.fill_color[0] = 0.0f;
			br.fill_color[1] = 0.0f;
			br.fill_color[2] = 0.0f;
		}
		graphics::drawText(50, 440, 23, "back", br);

		//Controls Information__________________________
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;
		graphics::setFont("assets\\newGame.ttf");
		graphics::drawText(60, 190, 20, "Walk....................................................W,A,S,D", br);
		graphics::drawText(60, 225, 20, "Run..............................................................LSHIFT", br);
		graphics::drawText(60, 260, 20, "Interact......................(hold)SPACE", br);
		graphics::drawText(60, 295, 20, "Pause....................................................................P", br);
		graphics::drawText(60, 330, 20, "Resume...............................................................O", br);
	}
}

bool StartScreen::getExit()
{
	return exit;
}

bool StartScreen::getgameStart()
{
	return gameStart;
}

bool StartScreen::cursor_loc(int high, int low, int right, int left)
{
	graphics::MouseState ms;
	graphics::getMouseState(ms);
	return EscapeRoom.windowToCanvas_x(ms.cur_pos_x) > left && EscapeRoom.windowToCanvas_x(ms.cur_pos_x) < right && EscapeRoom.windowToCanvas_y(ms.cur_pos_y) > high && EscapeRoom.windowToCanvas_y(ms.cur_pos_y) < low;

}

StartScreen::StartScreen(Game& mygame)
	:EscapeRoom(mygame)
{
}

StartScreen::~StartScreen()
{
}
