#include "Entity.h"


Entity::Entity(int spriteNum, int x, int y)
{
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
	this->x = x;
	this->y = y;
}


