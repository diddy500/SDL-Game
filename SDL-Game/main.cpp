#pragma once

#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "Cleanup.h"
#include "Window.h"


int main(int argc, char *argv[])
{


	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	Window win("res/curses_square_16x16.bmp", 640, 480, 16, 16);

	SDL_Event e;
	bool quit = false;

	while (!quit)
	{
		while (SDL_PollEvent(&e)){
			if (e.type == SDL_QUIT)
				quit = true;
			//Use number input to select which clip should be drawn
			if (e.type == SDL_KEYDOWN){

				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					quit = true;
				}
			}
		}

		win.updateWindow();

	}
	SDL_Quit();
	return 0;
}