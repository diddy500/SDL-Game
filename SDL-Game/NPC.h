#pragma once
#include "Entity.h"
class NPC :
	public Entity
{
public:
	NPC(std::list<Entity*>* list, int spriteNum, int maxX, int maxY, int x, int y);
	~NPC();

	//0-3 = up,right,down,left
	void Move(int dir);
};

