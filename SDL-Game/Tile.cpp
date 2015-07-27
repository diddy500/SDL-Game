#include "Tile.h"
#include <iostream>
#include <fstream>
#include <random>


Tile::Tile(std::string id, int spriteNum, int colourMod, bool isWalkable) : id(id)
{
	this->spriteNum = spriteNum;
	this->isWalkable = isWalkable;
	this->colourMod = colourMod;
}


Tile::~Tile()
{
}
