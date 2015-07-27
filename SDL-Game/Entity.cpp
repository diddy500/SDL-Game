#include "Entity.h"
#include "Level.h"

Entity::Entity(std::string id, int spriteNum, int colourMod, bool isWalkable, Level* lev, int maxX, int maxY, int x, int y) : Tile(id, spriteNum, colourMod, isWalkable)
{
	this->maxX = maxX;
	this->maxY = maxY;
	this->lev = lev;
	
	SetPos(x, y);
	lev->tokenList.push_back(this);
}


Entity::~Entity()
{
	lev->tokenList.remove(this);
}


int Entity::GetX(void)
{
	return x;
}
int Entity::GetY(void)
{
	return y;
}


void Entity::SetPos(int x, int y)
{
	if (x >= 0 && x < maxX)
		this->x = x;
	if (y >= 0 && y < maxY)
		this->y = y;
}


