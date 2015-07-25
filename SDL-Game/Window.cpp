#include "Window.h"


Window::Window(std::string sheetPath, int screenW, int screenH, int spriteW, int spriteH) : SCREEN_WIDTH(screenW), SCREEN_HEIGHT(screenH), lev(screenW, screenH)
{
	window = SDL_CreateWindow("Dorfs", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
	}

	sheet = new SpriteSheet(sheetPath, renderer, spriteW, spriteH);

	lev.GenerateLevel();

	for (int i = 0; i < SCREEN_HEIGHT / sheet->GetSpriteHeight(); i++)
	{
		for (int j = 0; j < SCREEN_WIDTH / sheet->GetSpriteWidth(); j++)
		{
			screenTiles.push_back(lev.GetBackgroundTile(j, i));
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

	SDL_RenderClear(renderer);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (lev.GetTokenTile(j, i) > 0)
				screenTiles[j + i * col] = lev.GetTokenTile(j, i);
			else
				screenTiles[j + i * col] = lev.GetBackgroundTile(j, i);
			
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

