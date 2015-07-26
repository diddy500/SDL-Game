#pragma once

#include <SDL.h>
#include <list>

class Entity
{
protected:
	int spriteNum;
	int maxX;
	int maxY;
	int x;
	int y;
	std::list<Entity*>* list;

public:
	Entity(std::list<Entity*>* list, int spriteNum, int maxX, int maxY, int x, int y);
	~Entity();

	int GetSpriteNum(void);
	int GetX(void);
	int GetY(void);

	void SetSpriteNum(int spriteNum);
	void SetPos(int x, int y);

	virtual void Move(int) = 0;
};

