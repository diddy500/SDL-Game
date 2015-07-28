#include "Window.h"


Window::Window(SDL_Window* window, SDL_Renderer* renderer, SpriteSheet* sheet, Level* lev,Entity* camFollow, int screenW, int screenH) : SCREEN_WIDTH(screenW), SCREEN_HEIGHT(screenH)
{
	this->window = window;
	this->renderer = renderer;
	this->sheet = sheet;
	this->lev = lev;
	this->entCamFollows = camFollow;

	for (int i = 0; i < SCREEN_HEIGHT / sheet->GetSpriteHeight(); i++)
	{
		for (int j = 0; j < SCREEN_WIDTH / sheet->GetSpriteWidth(); j++)
		{
			screenTiles.push_back(lev->GetBackgroundTile(j, i));
		}
	}
}


Window::~Window()
{
	cleanup(window, renderer);
	delete sheet;
}


void Window::updateWindow()
{
	int col = SCREEN_WIDTH / sheet->GetSpriteWidth();
	int row = SCREEN_HEIGHT / sheet->GetSpriteHeight();

	int offsetX = entCamFollows->GetX() - col / 2;
	int offsetY = entCamFollows->GetY() - row / 2;

	
	SDL_RenderClear(renderer);
	

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (lev->GetTokenTile(j + offsetX, i + offsetY) && lev->GetTokenTile(j + offsetX, i + offsetY)->isVisible)
				screenTiles[j + i * col] = lev->GetTokenTile(j + offsetX, i + offsetY);
			else
			{
					screenTiles[j + i * col] = lev->GetBackgroundTile(j + offsetX, i + offsetY);
			}
			
		}
	}

	int fps = counter.GetFPS();
	int fps1 = fps / 10;
	int fps2 = fps % 10;

	switch (fps1)
	{
	case 0:
		fps1 = NUM_0;
		break;
	case 1:
		fps1 = NUM_1;
		break;
	case 2:
		fps1 = NUM_2;
		break;
	case 3:
		fps1 = NUM_3;
		break;
	case 4:
		fps1 = NUM_4;
		break;
	case 5:
		fps1 = NUM_5;
		break;
	case 6:
		fps1 = NUM_6;
		break;
	case 7:
		fps1 = NUM_7;
		break;
	case 8:
		fps1 = NUM_8;
		break;
	case 9:
		fps1 = NUM_9;
		break;

	}
	switch (fps2)
	{
	case 0:
		fps2 = NUM_0;
		break;
	case 1:
		fps2 = NUM_1;
		break;
	case 2:
		fps2 = NUM_2;
		break;
	case 3:
		fps2 = NUM_3;
		break;
	case 4:
		fps2 = NUM_4;
		break;
	case 5:
		fps2 = NUM_5;
		break;
	case 6:
		fps2 = NUM_6;
		break;
	case 7:
		fps2 = NUM_7;
		break;
	case 8:
		fps2 = NUM_8;
		break;
	case 9:
		fps2 = NUM_9;
		break;

	}

	int sprite;
	int colourMod;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (j + i * col == 0)
			{
				sprite = fps1;
				colourMod = NULL;
			}
			else if (j + i * col == 1)
			{
				sprite = fps2;
				colourMod = NULL;

			}
			else if (screenTiles[j + i * col] && screenTiles[j + i * col]->isVisible)
			{
				sprite = screenTiles[j + i * col]->spriteNum;
				colourMod = screenTiles[j + i * col]->colourMod;
			}
			else if (screenTiles[j + i * col] && screenTiles[j + i * col]->isMemorized)
			{
				sprite = screenTiles[j + i * col]->spriteNum;
				colourMod = 0xAAAAAA;
			}
			else
			{
				sprite = 0;
				colourMod = NULL;
			}
			sheet->renderTexture(j * sheet->GetSpriteWidth(), i * sheet->GetSpriteHeight(), sprite, colourMod);
		}
	}
	
	SDL_RenderPresent(renderer);
	counter.checkFPS();
}

void Window::SetScreenTile(int x, int y, Tile* tile)
{
	screenTiles[x + y * SCREEN_WIDTH / sheet->GetSpriteWidth()] = tile;
}
Tile* Window::GetScreenTile(int x, int y)
{
	return screenTiles[x + y * SCREEN_WIDTH / sheet->GetSpriteWidth()];
}

