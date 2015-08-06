#include "stdafx.h"
#include "GameController.h"


GameController::GameController(std::string file, const int resX, const int resY, const int levelWidth, const int levelHeight, const int spriteWidth, const int spriteHeight) : levelTiles(levelWidth, levelHeight), screen(resX / spriteWidth, resY / spriteHeight), console(resX / spriteWidth / 5, resY / spriteHeight), displayControler(std::shared_ptr<DisplayControler>(new DisplayControler(file, spriteWidth, spriteHeight, resX, resY)))
{
	
}

GameController::~GameController()
{
}

bool GameController::updateGame()
{
	bool isRunning = true;
	while (SDL_PollEvent(&e)) 
	{

		switch (e.type)
		{
		case SDL_QUIT:
			isRunning = false;
			return isRunning;
			break;
		case SDL_KEYDOWN:
			if (e.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
				return isRunning;
			}
			break;
		default:
			break;
		}

		
	}
	return isRunning;
}

void GameController::displayGame()
{
	int num = 0;
	for (int i = 0; i < screen.HEIGHT; i++)
	{
		for (int j = 0; j < screen.WIDTH; j++)
		{
			if (num < 255)
				screen.SetTile(j, i, std::shared_ptr<Tile>(new Tile("type","blah", num++, 0xFFFFFF, true)));
			else
				num = 0;
		}
	}

	displayControler->renderScreen(screen);
}
