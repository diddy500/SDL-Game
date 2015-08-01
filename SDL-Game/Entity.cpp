#include "Entity.h"
#include "Level.h"

Entity::Entity(std::string id, std::string type, int spriteNum, int colourMod, bool isWalkable, Level* lev, int maxX, int maxY, int x, int y) : Tile(id, type, spriteNum, colourMod, isWalkable)
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


void Entity::SetPos(int newX, int newY)
{
	if (newX >= 0 && newX < maxX)
		this->x = newX;
	if (newY >= 0 && newY < maxY)
		this->y = newY;
}


