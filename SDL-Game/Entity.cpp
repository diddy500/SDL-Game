#include "Entity.h"


Entity::Entity(int spriteNum, int maxX, int maxY, int x, int y)
{
	this->maxX = maxX;
	this->maxY = maxY;
	SetSpriteNum(spriteNum);
	SetPos(x, y);
}


Entity::~Entity()
{
}


int Entity::GetSpriteNum(void)
{
	return spriteNum;
}
int Entity::GetX(void)
{
	return x;
}
int Entity::GetY(void)
{
	return y;
}



void Entity::SetSpriteNum(int spriteNum)
{
	this->spriteNum = spriteNum;
}
void Entity::SetPos(int x, int y)
{
	if (x >= 0 && x < maxX)
		this->x = x;
	if (y >= 0 && y < maxY)
		this->y = y;
}


