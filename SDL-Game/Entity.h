#pragma once

#include <SDL.h>

class Entity
{
protected:
	int spriteNum;

	int x;
	int y;

public:
	Entity(int spriteNum, int x = 0, int y = 0);
	~Entity();

	int GetSpriteNum(void);
	int GetX(void);
	int GetY(void);

	void SetSpriteNum(int spriteNum);
	void SetPos(int x, int y);

};

