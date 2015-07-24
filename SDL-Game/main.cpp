#include <SDL.h>
#include <iostream>
#include <string>
#include <vector>
#include "Cleanup.h"



void logSDLError(std::ostream &os, const std::string &msg)
{
	os << msg << " error: " << SDL_GetError() << std::endl;
}

SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren)
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

void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, SDL_Rect dst, SDL_Rect* clip = nullptr)
{
	SDL_RenderCopy(ren, tex, clip, &dst);
}
void renderTexture(SDL_Texture* tex, SDL_Renderer* ren, int x, int y, SDL_Rect* clip = nullptr)
{
	SDL_Rect dst;
	dst.x = x;
	dst.y = y;

	if (clip != nullptr)
	{
		dst.w = clip->w;
		dst.h = clip->h;
	}
	else
	{
		SDL_QueryTexture(tex, NULL, NULL, &dst.w, &dst.h);
	}

	renderTexture(tex, ren, dst, clip);
}

void updateWindow(SDL_Texture* sheet, SDL_Renderer* ren, std::vector<SDL_Rect> clips, const int screenW, const int screenH, const int spriteW, const int spriteH)
{
	int col = screenW / spriteW;
	int row = screenH / spriteH;

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			renderTexture(sheet, ren, j * spriteW, i * spriteH, &clips[(i)]);
		}
	}
}


int main(int argc, char *argv[])
{

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		logSDLError(std::cout, "SDL_Init");
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("Lesson 2", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		logSDLError(std::cout, "CreateWindow");
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		logSDLError(std::cout, "CreateRenderer");
		cleanup(window);
		SDL_Quit();
		return 1;
	}

	SDL_Texture *image = loadTexture("res/curses_square_16x16.bmp", renderer);
	if (image == nullptr)
	{
		cleanup(image, renderer, window);
		SDL_Quit();
		return 1;
	}

	//iW and iH are the clip width and height
	//We'll be drawing only clips so get a center position for the w/h of a clip
	int iW = 16, iH = 16;
	int x = SCREEN_WIDTH / 2 - iW / 2;
	int y = SCREEN_HEIGHT / 2 - iH / 2;

	//Setup the clips for our image
	std::vector<SDL_Rect> clips;

	SDL_Rect sheet;
	SDL_QueryTexture(image, NULL, NULL, &sheet.w, &sheet.h);

	for (int i = 0; i < (sheet.h / iH); ++i)
	{
		for (int j = 0; j < (sheet.w / iW); ++j)
		{
			SDL_Rect rect;
			rect.x = (j * 16);
			rect.y = (i * 16);
			rect.w = iW;
			rect.h = iH;
			clips.push_back(rect);

		}
	}
	//Specify a default clip to start with
	int useClip = 0;

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

		

		SDL_RenderClear(renderer);
		updateWindow(image, renderer, clips, SCREEN_WIDTH, SCREEN_HEIGHT, iW, iH);
		SDL_RenderPresent(renderer);

	}

	cleanup(image, renderer, window);
	SDL_Quit();
	return 0;
}