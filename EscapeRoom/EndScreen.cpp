#include "EndScreen.h"

bool EndScreen::getGoToStartScreen()
{
	return goToStartScreen;
}

void EndScreen::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_M)) {
		goToStartScreen = true;
	}
	if (x < 35 && graphics::getGlobalTime() > time + 2000) {
		x += 10 * graphics::getDeltaTime() / 250;
	}
	if (graphics::getGlobalTime() < time + 22000) {
		op += 0.03 * graphics::getDeltaTime() / 1000;
	}
	else {

		op += 0.07 * graphics::getDeltaTime() / 1000;
	}

}

void EndScreen::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.texture = "";
	br.fill_opacity = 1.0f;
	graphics::drawRect(CANVAS / 2, CANVAS / 2, CANVAS, CANVAS, br);
	br.texture = "assets\\ending.png";
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = op;
	graphics::drawRect(CANVAS / 2, 290, 480, 320, br);


	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 1.0f;
	graphics::setFont("assets\\message_font.ttf");
	if (graphics::getGlobalTime() > time + 2000 && graphics::getGlobalTime() < time +6000) {
		graphics::drawText(132, 40, x, "SURPRISE!!!", br);
	}else if (graphics::getGlobalTime() > time + 3000 && graphics::getGlobalTime() < time + 9000) {
		graphics::drawText(125, 40, x, "Did you forget?", br);
	}else if (graphics::getGlobalTime() > time + 3000 && graphics::getGlobalTime() < time +11000) {
		graphics::drawText(135, 40, x, "you silly goose...", br);
	}else if (graphics::getGlobalTime() > time + 3000 && graphics::getGlobalTime() < time +14500) {
		graphics::drawText(110, 40, x, "Its your birthday!", br);
	}else if (graphics::getGlobalTime() > time + 3000 && graphics::getGlobalTime() < time +18000 ) {
		graphics::drawText(157, 40, 23, "....or at least there is", br);
		graphics::drawText(165, 65, 23, "a 1/365 chance it is", br);
	}else if (graphics::getGlobalTime() > time + 3000 && graphics::getGlobalTime() < time + 22000 ) {
		graphics::drawText(150, 40, 23, "if not i still hope you ", br);
		graphics::drawText(200, 65, 23, "had fun :)", br);
	}else if (graphics::getGlobalTime() > time + 3000){
		graphics::drawText(100, 40, 35, "so Happy Birthday", br);
		graphics::drawText(95, 75, 30, "and thanks for playing!", br);
	}
	if (graphics::getGlobalTime() > time + 2000) {
		br.fill_opacity = 0.35f;
		graphics::drawText(150, 470, 16, "press <M> to skip ending", br);
	}
}

EndScreen::EndScreen()
{
	time = graphics::getGlobalTime();
}

EndScreen::~EndScreen()
{
}
