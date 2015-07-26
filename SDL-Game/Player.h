#pragma once
#include "Entity.h"
class Player :
	public Entity
{
public:
	Player(std::list<Entity*>* list, int maxX, int maxY, int x, int y);
	~Player();

	bool isPlayerTurn;

	void Move(int keynum);
};

