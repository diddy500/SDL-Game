#pragma once
#include <SDL.h>
#include "Utilities.h"
#include "Cleanup.h"
#include <vector>

class SpriteSheet
{
private:
	SDL_Texture* texture;
	SDL_Renderer* ren;
	int width;
	int height;
	int sW;
	int sH;
	std::vector<SDL_Rect> clips;
public:
	SpriteSheet(std::string filePath, SDL_Renderer* renderer, int spriteW, int spriteH);
	~SpriteSheet();

	SDL_Texture* GetTexture(void);
	int GetWidth(void);
	int GetHeight(void);
	int GetSpriteWidth(void);
	int GetSpriteHeight(void);

	SDL_Texture* loadTexture(const std::string &file);
	void loadSpriteSheet();

	void renderTexture(SDL_Rect dst, int useClip, int colourMod = 0xFFFFFF);
	void renderTexture(int x, int y, int useClip, int colourMod = 0xFFFFFF);
};

