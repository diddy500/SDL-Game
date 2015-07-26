#pragma once

#include <SDL.h>
#include <list>
#include <vector>
#include "Tile.h"
class Level;
class Entity
{
protected:
	int spriteNum;
	int maxX;
	int maxY;
	int x;
	int y;
	Level* lev;
public:
	Entity(Level* lev, int spriteNum, int maxX, int maxY, int x, int y);
	~Entity();

	int GetSpriteNum(void);
	int GetX(void);
	int GetY(void);

	void SetSpriteNum(int spriteNum);
	void SetPos(int x, int y);

	virtual void Move(int) = 0;
};

