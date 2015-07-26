#include "Tile.h"
#include <iostream>
#include <fstream>
#include <random>


Tile::Tile(std::string id, std::vector<int> spriteNums, bool isWalkable)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(0, spriteNums.size() - 1);

	this->id = id;
	this->spriteNum = spriteNums[dist(mt)];
	this->isWalkable = isWalkable;
}


Tile::~Tile()
{
}
