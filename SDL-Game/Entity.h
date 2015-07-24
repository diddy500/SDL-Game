#pragma once

#include <SDL.h>
#include "Window.h"

class Entity
{
protected:
	int spriteNum;
	int oldX;
	int oldY;
	int x;
	int y;
	Window* win;

	void moveHelper();
public:
	Entity(Window* win, int spriteNum, int x = 0, int y = 0);
	~Entity();

	int GetSpriteNum(void);
	int GetX(void);
	int GetY(void);
	int GetOldX(void);
	int GetOldY(void);

	void SetSpriteNum(int spriteNum);
	void SetPos(int x, int y);
	void SetOldPos(int x, int y);

	void Update();
};

