#pragma once

#include <Windows.h>
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "Cleanup.h"
#include "Window.h"
#include "Player.h"


int main(int argc, char *argv[])
{
	//config information
	const int LEVEL_WIDTH = 200;
	const int LEVEL_HEIGHT = 200;
	const int SCREEN_WIDTH = 1600;
	const int SCREEN_HEIGHT = 900;
	const int SPRITE_WIDTH = 16;
	const int SPRITE_HEIGHT = 16;
	const std::string SHEET_PATH = "Resources/curses_square_16x16.bmp";


	//Init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Dorfs", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
	}

	SpriteSheet* sheet = new SpriteSheet(SHEET_PATH, renderer, SPRITE_WIDTH, SPRITE_HEIGHT);

	Level* lev = new Level(LEVEL_WIDTH, LEVEL_HEIGHT);

	

	Window win(window, renderer, sheet, lev, lev->player, SCREEN_WIDTH, SCREEN_HEIGHT);

	
	//gameLoop
	const int TICKS_PER_SECOND = 50;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 10;

	DWORD next_game_tick = GetTickCount();
	int loops;

	SDL_Event e;
	bool quit = false;
	
	while (!quit)
	{
		loops = 0;
		while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP)
		{
			while (SDL_PollEvent(&e)){
				if (e.type == SDL_QUIT)
					quit = true;
				//User Input
				if (e.type == SDL_KEYDOWN){

					int keynum = e.key.keysym.sym;

					if (keynum == SDLK_ESCAPE)
					{
						quit = true;
					}
					lev->player->Move(e.key.keysym.sym);

				}
			}

			next_game_tick += SKIP_TICKS;
			loops++;
		}

		win.updateWindow();

	}
	SDL_Quit();
	return 0;
}