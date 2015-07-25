#pragma once

#include <SDL.h>
#include <vector>
#include "Utilities.h"
#include "Cleanup.h"
#include "SpriteSheet.h"
#include "Level.h"

class Window
{
private:
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SpriteSheet* sheet;
	Level* lev;
	Entity* entCamFollows;
	std::vector<int> screenTiles;

public:
	Window(SDL_Window* window, SDL_Renderer* renderer, SpriteSheet* sheet, Level* lev,Entity* camFollow, int screenW, int screenH);
	~Window();

	void updateWindow();
	void SetScreenTile(int x, int y, int spriteNum);
	int GetScreenTile(int x, int y);

};

