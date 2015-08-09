#pragma once

#include <list>
#include <memory>

#include "TileMap.h"
#include "Level.h"
#include "Entity.h"
#include "DisplayControler.h"
#include "InputController.h"
#include "MovementController.h"
#include "FOV\fov.h"

class GameController
{
public:
	GameController(std::string file, const int resX, const int resY, const int levelWidth, const int levelHeight, const int spriteWidth, const int spriteHeight);
	~GameController();

	bool updateGame();
	void displayGame();
private:
	SDL_Event e;
	Level levelTiles;
	TileMap screen;
	TileMap console;
	std::shared_ptr<std::list<std::shared_ptr<Entity>>> entityList;
	DisplayControler displayControler;
	InputController inputController;
	MovementController movementController;

	std::shared_ptr<Entity> player;
	fov_settings_type settings;

};