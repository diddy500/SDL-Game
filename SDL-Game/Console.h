#pragma once
#include <vector>
#include <memory>
#include "Tile.h"
#include "SpriteSheet.h"


class Console
{
private:
	const int COLS;
	const int ROWS;
	std::vector<std::shared_ptr<Tile>> consoleTileSprites;
public:
	Console(int width, int height);
	~Console();

	
};

