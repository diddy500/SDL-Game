#include <SDL.h>
#include <iostream>
#include "Cleanup.h"

int main(int argc, char *argv[])
{
	//start SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Create Window
	SDL_Window* win = SDL_CreateWindow("Hello World!", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (win == nullptr)
	{
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		cleanup(win);
		SDL_Quit();
		return 1;
	}

	//Create Renderer
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL)
	{
		cleanup(win, ren);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//Loading Bitmap
	std::string imagePath = "res/hello.bmp";
	SDL_Surface* bmp = SDL_LoadBMP(imagePath.c_str());
	if (bmp == nullptr)
	{
		cleanup(win, ren, bmp);
		std::cout << "SDL_LoadBMP Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	
	//Createing Texture
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, bmp);
	cleanup(bmp);
	if (tex == nullptr)
	{
		std::cout << "SDL_CreateTextureFromSurface Error: " << SDL_GetError() << std::endl;
		cleanup(win, ren, bmp, tex);
		SDL_Quit();
		return 1;
	}

	//Render Loop, waits 3 seconds
	for (int i = 0; i < 10; ++i)
	{
		//Clearing Renderer
		SDL_RenderClear(ren);
		//Drawing texture
		SDL_RenderCopy(ren, tex, NULL, NULL);
		//Update screen
		SDL_RenderPresent(ren);
		//pause
		SDL_Delay(1000);
	}

	cleanup(win, ren, tex);
	SDL_Quit();
	return 0;
}