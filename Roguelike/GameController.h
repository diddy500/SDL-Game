#pragma once

#include <list>
#include <memory>

#include "TileMap.h"
#include "Entity.h"

class GameController
{
public:
	GameController(const int resX, const int resY, const int levelWidth, const int levelHeight, const int spriteWidth, const int spriteHeight);
	~GameController();

	void updateGame();
	void displayGame();
private:
	TileMap levelTiles;
	TileMap screen;
	TileMap console;
	std::list<std::shared_ptr<Entity>> entityList;
};