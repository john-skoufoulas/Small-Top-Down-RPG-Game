#include "Map.h"
#include "iostream"

void Map::printGrid()
{
	for (int i = 0; i < MAP_GRID; i++) {
		for (int j = 0; j < MAP_GRID; j++) {
			std::cout << this->grid[i][j];
		}
		std::cout << std::endl;
	}
}

int Map::getGridTile(int i, int j)
{
	return grid[j][i];
}

void Map::updateMap(int i, int j, int t)
{
	this->grid[j][i] = t;
}

void Map::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0;
	br.texture = "assets\\" + background;
	graphics::drawRect(CANVAS / 2, CANVAS / 2, CANVAS, CANVAS, br);

	for (int i = 0; i < MAP_GRID; i++) {
		for (int j = 0; j < MAP_GRID; j++) {
			if (grid[i][j] == 1) {

			}
		}
	}

}

void Map::init()
{
}


Map::Map(std::string image, std::vector<std::vector <int>>& grid_array)
{
	this->background = image;
	for (int i = 0; i < MAP_GRID; i++) {
		for (int j = 0; j < MAP_GRID; j++) {
			this->grid[i][j] = grid_array[i][j];
		}
	}
}

Map::~Map()
{
}
