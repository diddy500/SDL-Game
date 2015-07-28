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
#include "Tile.h"
#include "TileLoader.h"

int main(int argc, char *argv[])
{
	//getting config information
	TCHAR tempPath[255];
	GetPrivateProfileString("video", "sprite_sheet", "Resources/curses_square_16x16.bmp", tempPath, 255, "Config/config.ini");
	const int LEVEL_WIDTH = GetPrivateProfileInt("level", "width", 500, "Config/config.ini");
	const int LEVEL_HEIGHT = GetPrivateProfileInt("level", "height", 500, "Config/config.ini");
	const int SCREEN_WIDTH = GetPrivateProfileInt("video", "res_x", 500, "Config/config.ini");
	const int SCREEN_HEIGHT = GetPrivateProfileInt("video", "res_y", 500, "Config/config.ini");
	const int SPRITE_WIDTH = GetPrivateProfileInt("video", "sprite_width", 500, "Config/config.ini");
	const int SPRITE_HEIGHT = GetPrivateProfileInt("video", "sprite_height", 500, "Config/config.ini");
	const std::string SHEET_PATH = tempPath;

	TileLoader loader;
	std::vector<TileLoader*> loaders = loader.GetAllOfType("Tiles", "floor");

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

	ULONGLONG next_game_tick = GetTickCount64();
	int loops;

	SDL_Event e;
	bool quit = false;
	
	while (!quit)
	{
		loops = 0;
		while (GetTickCount64() > next_game_tick && loops < MAX_FRAMESKIP)
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

			lev->UpdateLevel();

			next_game_tick += SKIP_TICKS;
			loops++;
		}

		
		win.updateWindow();

	}
	SDL_Quit();
	return 0;
}