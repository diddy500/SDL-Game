#include "NPC.h"
#include "Level.h"

NPC::NPC(Level* lev, int spriteNum, int maxX, int maxY, int x, int y) : Entity(lev, spriteNum, maxX, maxY, x, y)
{
}


NPC::~NPC()
{
}

void NPC::Move(int dir)
{
	enum MyEnum
	{
		UP,RIGHT,DOWN,LEFT
	};
	switch (dir)
	{
	case RIGHT:
		SetPos(GetX() + 1, GetY());
		break;
	case LEFT:
		SetPos(GetX() - 1, GetY());
		break;
	case UP:
		SetPos(GetX(), GetY() - 1);
		break;
	case DOWN:
		SetPos(GetX(), GetY() + 1);
		break;
	}
}