#pragma once

#include <Windows.h>
#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "Cleanup.h"
#include "Window.h"
#include "Cursor.h"


int main(int argc, char *argv[])
{


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	Window win("Resources/curses_square_16x16.bmp", 640, 480, 16, 16);
	Cursor cur(&win, 254, 10, 10);

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
				//Use number input to select which clip should be drawn
				if (e.type == SDL_KEYDOWN){

					int keynum = e.key.keysym.sym;

					if (keynum == SDLK_ESCAPE)
					{
						quit = true;
					}
					cur.Move(keynum);
				}
			}

			cur.Update();

			next_game_tick += SKIP_TICKS;
			loops++;
		}

		win.updateWindow();

	}
	SDL_Quit();
	return 0;
}