#pragma once

#include <SDL.h>
#include <vector>
#include "Utilities.h"
#include "Cleanup.h"
#include "SpriteSheet.h"
#include "Level.h"
#include "Tile.h"
#include "FPSCounter.h"

class Window
{
private:

	enum SheetChars
	{
		NUM_0 = 48,
		NUM_1,
		NUM_2,
		NUM_3,
		NUM_4,
		NUM_5,
		NUM_6,
		NUM_7,
		NUM_8,
		NUM_9,
	};

	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;

	FPSCounter counter;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SpriteSheet* sheet;
	Level* lev;
	Entity* entCamFollows;
	std::vector<Tile*> screenTiles;

public:
	Window(SDL_Window* window, SDL_Renderer* renderer, SpriteSheet* sheet, Level* lev,Entity* camFollow, int screenW, int screenH);
	~Window();

	void updateWindow();
	void SetScreenTile(int x, int y, Tile* tile);
	Tile* GetScreenTile(int x, int y);

};

