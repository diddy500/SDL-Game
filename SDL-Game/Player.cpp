#include "Player.h"


Player::Player(int maxX, int maxY, int x, int y) : Entity(2, maxX, maxY, x, y)
{
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
		break;
	case SDLK_LEFT:
		SetPos(GetX() - 1, GetY());
		break;
	case SDLK_UP:
		SetPos(GetX(), GetY() - 1);
		break;
	case SDLK_DOWN:
		SetPos(GetX(), GetY() + 1);
		break;
	default:
		break;
	}
}