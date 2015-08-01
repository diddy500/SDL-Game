#pragma once
#include "Entity.h"
class Player :
	public Entity
{
public:
	Player(std::string id, std::string type, int spriteNum, int colourMod, bool isWalkable, Level* lev, int maxX, int maxY, int x, int y);
	~Player();

	bool isPlayerTurn;

	void Move(int keynum);
	void CheckVision();
	void SeeTile(int checkX, int checkY);
};

