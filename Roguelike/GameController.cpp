#include "stdafx.h"
#include "GameController.h"

#include "EntityPrototype.h"


GameController::GameController(std::string file, const int resX, const int resY, const int levelWidth, const int levelHeight, const int spriteWidth, const int spriteHeight) : levelTiles(levelWidth, levelHeight), screen(resX / spriteWidth, resY / spriteHeight), console(resX / spriteWidth / 5, resY / spriteHeight), entityList(new std::list<std::shared_ptr<Entity>>), displayControler(file, spriteWidth, spriteHeight, resX, resY), inputController(entityList, movementController), movementController(entityList, levelTiles)
{
	levelTiles.generate(1000);
	player = std::shared_ptr<Entity>(new Entity(EntityPrototype::GetEntity("nobel", 1, 1)));
	player->isPlayer = true;
	entityList->push_back(player);
}

GameController::~GameController()
{
}

bool GameController::updateGame()
{
	while (SDL_PollEvent(&e)) 
	{

		switch (e.type)
		{
		case SDL_QUIT:
			return false;
			break;
		case SDL_KEYDOWN:
			if (!inputController.ProcessEvent(e))
				return false;
			break;
		default:
			break;
		}

		
	}
	return true;
}

void GameController::displayGame()
{
	int offsetX = player->GetPosition().x - screen.WIDTH / 2;
	int offsetY = player->GetPosition().y - screen.HEIGHT / 2;


	for (int y = 0; y < screen.HEIGHT; y++)
	{
		for (int x = 0; x < screen.WIDTH; x++)
		{
			screen.SetTile(x, y, levelTiles.GetTile(x + offsetX, y + offsetY));
		}
	}
	for (std::shared_ptr<Entity> ent : *entityList.get())
	{
		if (screen.inBounds(ent->GetPosition().x - offsetX, ent->GetPosition().y - offsetY))
		{
			screen.SetTile(ent->GetPosition().x - offsetX, ent->GetPosition().y - offsetY, ent->GetTileInfo());
		}
	}
	displayControler.renderScreen(screen);
}
