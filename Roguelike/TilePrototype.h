#pragma once

#include <vector>
#include "Tile.h"

class TilePrototype
{
public:
	TilePrototype();
	static const std::vector<TilePrototype> GetAllTiles();
	static const Tile GetTile(std::string id);
	~TilePrototype();

private:
	TilePrototype(std::string newID);

	std::string type;
	std::string id;
	std::vector<int> spriteNums;
	std::vector<int> colourMods;
	bool isWalkable;
	bool isOpaque;
};

