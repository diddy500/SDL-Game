#include "NPC.h"
#include "Level.h"

NPC::NPC(std::string id, std::string type, int spriteNum, int colourMod, bool isWalkable, Level* lev, int maxX, int maxY, int x, int y) : Entity(id, type, spriteNum, colourMod, isWalkable, lev, maxX, maxY, x, y)
{
}


NPC::~NPC()
{
}

void NPC::Move(int dir)
{
	lev->SetTokenTile(GetX(), GetY(), nullptr);
	enum MyEnum
	{
		UP, RIGHT, DOWN, LEFT, WAIT
	};
	switch (dir)
	{
	case RIGHT:
		if (lev->GetTile(GetX() + 1, GetY()) && lev->GetTile(GetX() + 1, GetY())->isWalkable)
			SetPos(GetX() + 1, GetY());
		break;
	case LEFT:
		if (lev->GetTile(GetX() - 1, GetY()) && lev->GetTile(GetX() - 1, GetY())->isWalkable)
			SetPos(GetX() - 1, GetY());
		break;
	case UP:
		if (lev->GetTile(GetX(), GetY() - 1) && lev->GetTile(GetX(), GetY() - 1)->isWalkable)
			SetPos(GetX(), GetY() - 1);
		break;
	case DOWN:
		if (lev->GetTile(GetX(), GetY() + 1) && lev->GetTile(GetX(), GetY() + 1)->isWalkable)
			SetPos(GetX(), GetY() + 1);
		break;
	case WAIT:
		break;
	}

	lev->SetTokenTile(GetX(), GetY(), this);
}