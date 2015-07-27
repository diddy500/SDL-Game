#pragma once

#include <SDL.h>
#include <vector>
#include "Utilities.h"
#include "Cleanup.h"
#include "SpriteSheet.h"
#include "Level.h"
#include "Tile.h"

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
	std::vector<Tile*> screenTiles;

public:
	Window(SDL_Window* window, SDL_Renderer* renderer, SpriteSheet* sheet, Level* lev,Entity* camFollow, int screenW, int screenH);
	~Window();

	void updateWindow();
	void SetScreenTile(int x, int y, Tile* tile);
	Tile* GetScreenTile(int x, int y);

};

