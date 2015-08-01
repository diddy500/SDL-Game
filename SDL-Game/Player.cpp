#include "Player.h"

#include <functional>

#include "Level.h"
#include "fov.h"

Player::Player(std::string id, std::string type, int spriteNum, int colourMod, bool isWalkable, Level* lev, int maxX, int maxY, int x, int y) : Entity(id, type, spriteNum, colourMod, isWalkable, lev, maxX, maxY, x, y)
{
	isPlayerTurn = false;
	isVisible = true;
	CheckVision();
}


Player::~Player()
{
}

void Player::Move(int keynum)
{
	bool hasMoved = false;
	//clearing old position
	lev->SetTokenTile(GetX(), GetY(), nullptr);

	switch (keynum)
	{
	case SDLK_RIGHT:
		if (lev->GetTile(GetX() + 1, GetY()) && lev->GetTile(GetX() + 1, GetY())->isWalkable)
		{
			SetPos(GetX() + 1, GetY());
			hasMoved = true;
		}
		break;
	case SDLK_LEFT:
		if (lev->GetTile(GetX() - 1, GetY()) && lev->GetTile(GetX() - 1, GetY())->isWalkable)
		{
			SetPos(GetX() - 1, GetY());
			hasMoved = true;
		}
		break;
	case SDLK_UP:
		if (lev->GetTile(GetX(), GetY() - 1) && lev->GetTile(GetX(), GetY() - 1)->isWalkable)
		{
			SetPos(GetX(), GetY() - 1);
			hasMoved = true;
		}
		break;
	case SDLK_DOWN:
		if (lev->GetTile(GetX(), GetY() + 1) && lev->GetTile(GetX(), GetY() + 1)->isWalkable)
		{
			SetPos(GetX(), GetY() + 1);
			hasMoved = true;
		}
		break;
	case SDLK_PERIOD:
		hasMoved = true;
		break;
	}

	if (hasMoved)
	{
		isPlayerTurn = false;
	}
	//setting new position
	lev->SetTokenTile(GetX(), GetY(), this);
	
}
void Player::CheckVision()
{
	fov(GetX(), GetY(), lev, this);
}
void Player::SeeTile(int checkX, int checkY)
{
	if (lev->GetBackgroundTile(checkX, checkY))
	{
		lev->GetBackgroundTile(checkX, checkY)->isVisible = true;
		lev->GetBackgroundTile(checkX, checkY)->isMemorized = true;
	}
	if (lev->GetTokenTile(checkX, checkY))
		lev->GetTokenTile(checkX, checkY)->isVisible = true;
}