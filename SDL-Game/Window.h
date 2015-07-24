#pragma once

#include <SDL.h>
#include "Utilities.h"
#include "Cleanup.h"
#include "SpriteSheet.h"

class Window
{
private:
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SpriteSheet* sheet;



public:
	Window(std::string sheetPath, int screenW, int screenH, int spriteW, int spriteH);
	~Window();

	void updateWindow();
};

