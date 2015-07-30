#include "Window.h"
#include <Windows.h>
#include "SheetEnum.h"



Window::Window(SDL_Window* window, SDL_Renderer* renderer, SpriteSheet* sheet, Level* lev,Entity* camFollow, int screenW, int screenH) : SCREEN_WIDTH(screenW), SCREEN_HEIGHT(screenH)
{
	this->window = window;
	this->renderer = renderer;
	this->sheet = sheet;
	this->lev = lev;
	this->entCamFollows = camFollow;

	col = SCREEN_WIDTH / sheet->GetSpriteWidth();
	row = SCREEN_HEIGHT / sheet->GetSpriteHeight();

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

void Window::UpdateScreenTile(int x, int y)
{
	int sprite;
	int colourMod;

	std::array<int, 2> fps = counter.GetFPS();

	if (x + y * col == 0)
	{
		sprite = fps[0];
		colourMod = NULL;
	}
	else if (x + y * col == 1)
	{
		sprite = fps[1];
		colourMod = NULL;

	}
	else if (GetScreenTile(x, y) && GetScreenTile(x, y)->isVisible)
	{
		sprite = GetScreenTile(x, y)->spriteNum;
		colourMod = GetScreenTile(x, y)->colourMod;
	}
	else if (GetScreenTile(x, y) && GetScreenTile(x, y)->isMemorized)
	{
		sprite = GetScreenTile(x, y)->spriteNum;
		colourMod = 0xAAAAAA;
	}
	else
	{
		sprite = 0;
		colourMod = NULL;
	}
	sheet->renderTexture(x * sheet->GetSpriteWidth(), y * sheet->GetSpriteHeight(), sprite, colourMod);
}

void Window::updateWindow()
{
	int offsetX = entCamFollows->GetX() - col / 2;
	int offsetY = entCamFollows->GetY() - row / 2;

	
	SDL_RenderClear(renderer);
	
	//getting screen tiles from 
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (lev->GetTokenTile(j + offsetX, i + offsetY) && lev->GetTokenTile(j + offsetX, i + offsetY)->isVisible)
				SetScreenTile(j, i, lev->GetTokenTile(j + offsetX, i + offsetY));
			else
			{
				SetScreenTile(j, i, lev->GetBackgroundTile(j + offsetX, i + offsetY));
			}
			
		}
	}

	

	
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			UpdateScreenTile(j, i);
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

