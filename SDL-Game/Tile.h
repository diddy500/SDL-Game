#pragma once

#include <string>
#include <json/json.h>
#include <vector>


class Tile
{
private:
	

public:
	Tile(std::string id, std::vector<int> spriteNums, bool isWalkable);
	~Tile();

	std::string id;
	int spriteNum;
	bool isWalkable;
};