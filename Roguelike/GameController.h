#pragma once

#include <list>
#include <memory>

#include "TileMap.h"
#include "Entity.h"
#include "DisplayControler.h"

class GameController
{
public:
	GameController(std::string file, const int resX, const int resY, const int levelWidth, const int levelHeight, const int spriteWidth, const int spriteHeight);
	~GameController();

	bool updateGame();
	void displayGame();
private:
	SDL_Event e;
	TileMap levelTiles;
	TileMap screen;
	TileMap console;
	std::list<std::shared_ptr<Entity>> entityList;
	std::shared_ptr<DisplayControler> displayControler;

	std::shared_ptr<Entity> player;
};