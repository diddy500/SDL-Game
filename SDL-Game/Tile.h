#pragma once

#include <string>
#include <json/json.h>
#include <vector>


class Tile
{
private:
	

public:
	Tile(std::string id, std::string type, int spriteNum, int colourMod, bool isWalkable);
	~Tile();

	std::string id;
	std::string type;
	int spriteNum;
	int colourMod;
	bool isWalkable;
	bool isMemorized = false;
	bool isVisible = false;
};