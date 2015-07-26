#include "Player.h"
#include "Level.h"

Player::Player(Level* lev, int maxX, int maxY, int x, int y) : Entity(lev, 1, maxX, maxY, x, y)
{
	isPlayerTurn = false;
}


Player::~Player()
{
}

void Player::Move(int keynum)
{
	
	switch (keynum)
	{
	case SDLK_RIGHT:
		SetPos(GetX() + 1, GetY());
		isPlayerTurn = false;
		break;
	case SDLK_LEFT:
		SetPos(GetX() - 1, GetY());
		isPlayerTurn = false;
		break;
	case SDLK_UP:
		SetPos(GetX(), GetY() - 1);
		isPlayerTurn = false;
		break;
	case SDLK_DOWN:
		SetPos(GetX(), GetY() + 1);
		isPlayerTurn = false;
		break;
	case SDLK_PERIOD:
		isPlayerTurn = false;
		break;
	}

	
}