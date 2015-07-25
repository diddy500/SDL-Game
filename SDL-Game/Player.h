#pragma once
#include "Entity.h"
class Player :
	public Entity
{
public:
	Player(int maxX, int maxY, int x, int y);
	~Player();

	void Move(int keynum);
};

