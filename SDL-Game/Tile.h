#pragma once

#include <string>
#include <json/json.h>
#include <vector>


class Tile
{
private:
	

public:
	Tile(std::string id, int spriteNum, int colourMod, bool isWalkable);
	~Tile();

	std::string id;
	int spriteNum;
	int colourMod;
	bool isWalkable;
	bool isVisible = false;
};