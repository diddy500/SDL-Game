#include "stdafx.h"
#include "DisplayControler.h"

#include "Utility.h"


DisplayControler::DisplayControler(std::string file, int spriteWidth, int spriteHeight, int screenWidth, int screenHeight) : _spriteWidth(spriteWidth), _spriteHeight(spriteHeight)
{
	//setup renderer and window
	_window = SDL_CreateWindow("Dorfs", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	//loading image
	SDL_Surface* loadedImage(SDL_LoadBMP(file.c_str()));

	//Makeing image into texture
	if (loadedImage)
	{
		SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0xFF, 0x00, 0xFF));
		_spritesheet = SDL_CreateTextureFromSurface(_renderer, loadedImage);
		SDL_FreeSurface(loadedImage);
	}
	else
		LogError("DisplayController: Error Loading image");

	//getting sheet size
	SDL_QueryTexture(_spritesheet, NULL, NULL, &_width, &_height);

	//getting position of each sprite off sheet
	for (int i = 0; i < _height / spriteHeight; i++)
	{
		for (int j = 0; j < _width / spriteWidth; j++)
		{
			SDL_Rect rect;
			rect.x = (j * spriteWidth);
			rect.y = (i * spriteHeight);
			rect.w = spriteWidth;
			rect.h = spriteHeight;
			_sprites.push_back(rect);
		}
	}
}

DisplayControler::~DisplayControler()
{
}

void DisplayControler::renderScreen(const TileMap & screen)
{
	SDL_RenderClear(_renderer);
	for (int i = 0; i < screen.HEIGHT; i++)
	{
		for (int j = 0; j < screen.WIDTH; j++)
		{
			if (screen.GetTile(j, i))
			{
				renderSprite(j * _spriteWidth, i * _spriteHeight, screen.GetTile(j, i)->spriteNum, screen.GetTile(j, i)->colourMod);
			}
		}
	}
	SDL_RenderPresent(_renderer);
}

void DisplayControler::renderSprite(const SDL_Rect & dst, const int useSprite, const int colourMod)
{
	Uint32 number;
	if (colourMod == NULL)
		number = 0xFFFFFF;
	else
		number = colourMod;

	Uint8 b = number & 0xFF;
	Uint8 g = (number >> 8) & 0xFF;
	Uint8 r = (number >> 16) & 0xFF;
	SDL_SetTextureColorMod(_spritesheet, r, g, b);
	SDL_RenderCopy(_renderer, _spritesheet, &_sprites[useSprite], &dst);
}

void DisplayControler::renderSprite(const int x, const int y, const int useSprite, const int colourMod)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = _spriteWidth;
	dst.h = _spriteHeight;

	renderSprite(dst, useSprite, colourMod);
}
