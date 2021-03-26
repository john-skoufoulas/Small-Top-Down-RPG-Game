#pragma once
#include "graphics.h"
#include "config.h"
#include "Movable_Object.h"
#include <string>
#include "iostream"
#include "vector"


class Map {
protected: 
	std::string background;
	int grid[MAP_GRID][MAP_GRID];
public:
	void printGrid();
	int getGridTile(int i, int j);
	void updateMap(int i, int j,  int t);
	void draw();
	void init();
	Map(std::string image,std::vector<std::vector <int>> &grid_array);
	~Map();
};