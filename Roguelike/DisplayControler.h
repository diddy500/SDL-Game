#pragma once
#include <SDL.h>
#include <memory>
#include <vector>
#include "TileMap.h"

class DisplayControler
{
public:
	DisplayControler(std::string file, int spriteWidth, int spriteHeight, int screenWidth, int screenHeight);
	~DisplayControler();

	void renderScreen(const TileMap& screen);
	
private:
	void renderSprite(const SDL_Rect &dst, const int useSprite, const int colourMod);
	void renderSprite(const int x, const int y, const int useSprite, const int colourMod);

	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Texture* _spritesheet;
	int _width;
	int _height;
	int _spriteWidth;
	int _spriteHeight;
	std::vector<SDL_Rect> _sprites;
};

