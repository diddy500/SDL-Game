#include "Entity.h"


Entity::Entity(Window* win, int spriteNum, int x, int y)
{
	this->win = win;
	SetSpriteNum(spriteNum);
	SetPos(x, y);
	SetOldPos(x, y);
}


Entity::~Entity()
{
}

void Entity::moveHelper()
{
	SetOldPos(GetX(), GetY());
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
int Entity::GetOldX(void)
{
	return oldX;
}
int Entity::GetOldY(void)
{
	return oldY;
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
void Entity::SetOldPos(int x, int y)
{
	this->oldX = x;
	this->oldY = y;
}

void Entity::Update()
{
	if (GetX() != GetOldX() || GetY() != GetOldY())
	{
		win->SetScreenTile(GetOldX(), GetOldY(), win->GetBackgroundTile(GetOldX(), GetOldY()));
		win->SetScreenTile(GetX(), GetY(), GetSpriteNum());
	}
}