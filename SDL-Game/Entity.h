#pragma once

#include <SDL.h>
#include <list>
#include <vector>
#include "Tile.h"
class Level;
class Entity : public Tile
{
protected:
	int maxX;
	int maxY;
	int x;
	int y;
	Level* lev;
public:
	Entity(std::string id, std::string type, int spriteNum, int colourMod, bool isWalkable, Level* lev, int maxX, int maxY, int x, int y);
	~Entity();

	int GetX(void);
	int GetY(void);

	void SetPos(int x, int y);

	virtual void Move(int) = 0;
};

