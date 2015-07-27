#include "SpriteSheet.h"
#include <exception>

SpriteSheet::SpriteSheet(std::string file, SDL_Renderer* renderer, int spriteW, int spriteH)
{

	sW = spriteW;
	sH = spriteH;

	ren = renderer;

	texture = loadTexture(file);
	if (texture == nullptr)
	{
		cleanup(texture);
		logSDLError(std::cout, "Bad image path");
	}

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);


	loadSpriteSheet();
}


SpriteSheet::~SpriteSheet()
{
	cleanup(texture);
}



SDL_Texture* SpriteSheet::GetTexture(void)
{
	return texture;
}
int SpriteSheet::GetWidth(void)
{
	return width;
}
int SpriteSheet::GetHeight(void)
{
	return height;
}
int SpriteSheet::GetSpriteWidth(void)
{
	return sW;
}
int SpriteSheet::GetSpriteHeight(void)
{
	return sH;
}

SDL_Texture* SpriteSheet::loadTexture(const std::string &file)
{
	SDL_Texture *texture = nullptr;
	SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());

	if (loadedImage != nullptr)
	{
		SDL_SetColorKey(loadedImage, SDL_TRUE, SDL_MapRGB(loadedImage->format, 0xFF, 0x00, 0xFF));

		texture = SDL_CreateTextureFromSurface(ren, loadedImage);
		cleanup(loadedImage);

		if (texture == nullptr)
			logSDLError(std::cout, "CreateTextureFromSurface");

	}
	else
	{
		logSDLError(std::cout, "LoadBMP");
	}
	return texture;
}

void SpriteSheet::loadSpriteSheet()
{
	for (int i = 0; i < height / sH; i++)
	{
		for (int j = 0; j < width / sW; j++)
		{
			SDL_Rect rect;
			rect.x = (j * sW);
			rect.y = (i * sH);
			rect.w = sW;
			rect.h = sH;
			clips.push_back(rect);
		}
	}
}


void SpriteSheet::renderTexture(SDL_Rect dst, int useClip, int colourMod)
{
	Uint32 number;
	if (colourMod == NULL)
		number = 0xFFFFFF;
	else
		number = colourMod;

	Uint8 b = number & 0xFF;
	Uint8 g = (number >> 8) & 0xFF;
	Uint8 r = (number >> 16) & 0xFF;
	SDL_SetTextureColorMod(texture, r, g, b);
	SDL_RenderCopy(ren, texture, &clips[useClip], &dst);
}
void SpriteSheet::renderTexture(int x, int y, int useClip, int colourMod)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = sW;
	dst.h = sH;

	renderTexture(dst, useClip, colourMod);
}