#include "Window.h"


Window::Window(std::string sheetPath, int screenW, int screenH, int spriteW, int spriteH) : SCREEN_WIDTH(screenW), SCREEN_HEIGHT(screenH)
{
	window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

}


Window::~Window()
{
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

			sheet->renderTexture(j * sheet->GetSpriteWidth(), i * sheet->GetSpriteHeight(), 2);
		}
	}

	SDL_RenderPresent(renderer);
}