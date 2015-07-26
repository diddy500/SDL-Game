#pragma once
#include "Entity.h"
class Player :
	public Entity
{
public:
	Player(Level* lev, int maxX, int maxY, int x, int y);
	~Player();

	bool isPlayerTurn;

	void Move(int keynum);
};

