#include "Tile.h"
#include <iostream>
#include <fstream>
#include <random>


Tile::Tile(std::string id, std::string type, int spriteNum, int colourMod, bool isWalkable) : id(id), type(type)
{
	this->spriteNum = spriteNum;
	this->isWalkable = isWalkable;
	this->colourMod = colourMod;
}


Tile::~Tile()
{
}
