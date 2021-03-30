#include "Credits.h"

void Credits::update()
{
	pos_y -= 10.0f * graphics::getDeltaTime() / 250;
	if (pos_y <= 93.0f) pos_y = 93.0f;
}

void Credits::draw()
{
	graphics::setFont("assets\\message_font.ttf");

	graphics::Brush br;
	br.outline_opacity = 0.0f;
	br.texture = "assets\\start_screen.png";
	graphics::drawRect(CANVAS / 2, CANVAS / 2, CANVAS, CANVAS, br);

	br.texture = "";

	br.fill_color[0] = 0.0f;
	br.fill_color[1] = 0.0f;
	br.fill_color[2] = 0.0f;
	br.fill_opacity = 0.55f;
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS / 2, CANVAS / 2, CANVAS * 0.7, CANVAS * 0.73, br);

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.fill_opacity = 1.0f;

	printInCenter("Creator:", 0, 21);
	printInCenter("Skoufoulas Ioannis", 1, 21);
	printInCenter("Github: https://github.com/Cryoticen", 2, 20);
	printInCenter("Artwork  with  the  help  of:", 3, 21);
	printInCenter("Deepnight Games : Map Editor 2", 4, 17);
	printInCenter("RachelTheSeeker", 5, 17);
	printInCenter("SchwarzeNacht", 6, 17);

	printInCenter("Moral  support:", 8, 21);
	printInCenter("Plateia Foivos Hliadhs", 9, 19);
	printInCenter("Iasonas Gym leader", 10, 19);

}

void Credits::printInCenter(std::string note, int row, int size)
{
	graphics::Brush br;
	graphics::drawText(CANVAS / 2 - note.length() *8 / 2, pos_y + 30* row, size, note, br);
}

Credits::Credits()
{
}

Credits::~Credits()
{
}
