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
	
	lev->UpdateLevel();

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			
			if (lev->GetTokenTile(j + offsetX, i + offsetY) > 0)
				screenTiles[j + i * col] = lev->GetTokenTile(j + offsetX, i + offsetY);
			else
				screenTiles[j + i * col] = lev->GetBackgroundTile(j + offsetX, i + offsetY);
			
		}
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{

			sheet->renderTexture(j * sheet->GetSpriteWidth(), i * sheet->GetSpriteHeight(), screenTiles[j + i * col]);
		}
	}
	
	SDL_RenderPresent(renderer);
}

void Window::SetScreenTile(int x, int y, int spriteNum)
{
	screenTiles[x + y * SCREEN_WIDTH / sheet->GetSpriteWidth()] = spriteNum;
}
int Window::GetScreenTile(int x, int y)
{
	return screenTiles[x + y * SCREEN_WIDTH / sheet->GetSpriteWidth()];
}

