#include "stdafx.h"
#include "GameController.h"

#include "EntityPrototype.h"
#include "Utility.h"

bool IsOpaque(void* map, int x, int y)
{
	Level* level(static_cast<Level*>(map));
	if (level->GetTile(x, y))
	{
		return level->GetTile(x, y)->isOpaque;
	}
	else
	{
		return false;
	}
}
//missing perams are reletive x and y and light source pointer
void LightTile(void* map, int x, int y, int , int , void*)
{
	Level* level(static_cast<Level*>(map));
	if (level->GetTile(x, y))
	{
		level->GetTile(x, y)->isVisible = true;
	}
}


GameController::GameController(std::string file, const int resX, const int resY, const int levelWidth, const int levelHeight, const int spriteWidth, const int spriteHeight) : levelTiles(levelWidth, levelHeight), screen(resX / spriteWidth, resY / spriteHeight), console(resX / spriteWidth / 5, resY / spriteHeight), entityList(new std::list<std::shared_ptr<Entity>>), displayControler(file, spriteWidth, spriteHeight, resX, resY), inputController(entityList, movementController), movementController(entityList, levelTiles)
{
	levelTiles.generate(50, entityList);
	
	for (std::shared_ptr<Entity> ent : *entityList)
	{
		if (ent->isPlayer)
		{
			player = ent;
			break;
		}
	}

	//setting up FOV
	fov_settings_init(&settings);
	fov_settings_set_opacity_test_function(&settings, IsOpaque);
	fov_settings_set_apply_lighting_function(&settings, LightTile);
}

GameController::~GameController()
{
}

bool GameController::updateGame()
{
	for (std::shared_ptr<Entity> ent : *entityList)
	{
		if (ent->isDead())
		{
			entityList->remove(ent);
		}
	}

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
	
	//reseting sight
	for (int y = 0; y < levelTiles.HEIGHT; y++)
	{
		for (int x = 0; x < levelTiles.WIDTH; x++)
		{
			if (levelTiles.GetTile(x, y)->isVisible)
			{
				levelTiles.GetTile(x, y)->isVisible = false;
				levelTiles.GetTile(x, y)->isMemorized = true;
			}
		}
	}

	//checking new sight
	fov_circle(&settings, &levelTiles, &player, player->GetPosition().x, player->GetPosition().y, 50);

	//checking for seen entities
	for (std::shared_ptr<Entity> ent : *entityList)
	{
		if (levelTiles.GetTile(ent->GetPosition())->isVisible || ent->isPlayer)
		{
			ent->GetTileInfo()->isVisible = true;
		}
		else
		{
			ent->GetTileInfo()->isVisible = false;
		}
	}

	int offsetX = player->GetPosition().x - screen.WIDTH / 2;
	int offsetY = player->GetPosition().y - screen.HEIGHT / 2;

	for (int y = 0; y < screen.HEIGHT; y++)
	{
		for (int x = 0; x < screen.WIDTH; x++)
		{
			screen.SetTile(x, y, levelTiles.GetTile(x + offsetX, y + offsetY));
		}
	}
	for (std::shared_ptr<Entity> ent : *entityList)
	{
		if (ent->GetTileInfo()->isVisible && screen.inBounds(ent->GetPosition().x - offsetX, ent->GetPosition().y - offsetY))
		{
			screen.SetTile(ent->GetPosition().x - offsetX, ent->GetPosition().y - offsetY, ent->GetTileInfo());
		}
	}
	displayControler.renderScreen(screen);
}

