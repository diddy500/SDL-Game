#pragma once

#include "TileMap.h"

class GameController
{
public:
	GameController();
	~GameController();

private:
	TileMap levelTiles;
	TileMap levelTokens;
	TileMap Console;
	TileMap screen;
};