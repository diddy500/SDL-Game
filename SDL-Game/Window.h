#pragma once

#include <SDL.h>
#include <vector>
#include "Console.h"
#include "Utilities.h"
#include "Cleanup.h"
#include "SpriteSheet.h"
#include "Level.h"
#include "Tile.h"
#include "FPSCounter.h"

class Window
{
private:
	const int SCREEN_WIDTH;
	const int SCREEN_HEIGHT;
	int col;
	int row;

	FPSCounter counter;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SpriteSheet* sheet;
	Level* lev;
	Console* console;
	Entity* entCamFollows;
	std::vector<Tile*> screenTiles;

	void UpdateScreenTile(int x, int y);
public:
	Window(SDL_Window* window, SDL_Renderer* renderer, SpriteSheet* sheet, Level* lev,Entity* camFollow, int screenW, int screenH);
	~Window();

	void updateWindow();
	void SetScreenTile(int x, int y, Tile* tile);
	Tile* GetScreenTile(int x, int y);

};

