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

	int sprite;
	int colourMod;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			
			if (screenTiles[j + i * col] && screenTiles[j + i * col]->isVisible)
			{
				sprite = screenTiles[j + i * col]->spriteNum;
				colourMod = screenTiles[j + i * col]->colourMod;
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
}

void Window::SetScreenTile(int x, int y, Tile* tile)
{
	screenTiles[x + y * SCREEN_WIDTH / sheet->GetSpriteWidth()] = tile;
}
Tile* Window::GetScreenTile(int x, int y)
{
	return screenTiles[x + y * SCREEN_WIDTH / sheet->GetSpriteWidth()];
}

