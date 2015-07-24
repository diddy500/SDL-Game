#include "Cursor.h"


Cursor::Cursor(Window* win, int spriteNum, int x, int y) : Entity(win, spriteNum, x, y)
{
}


Cursor::~Cursor()
{
}

void Cursor::Update()
{
	if (visible)
		if (GetX() != GetOldX() || GetY() != GetOldY())
		{
			win->SetScreenTile(GetOldX(), GetOldY(), win->GetBackgroundTile(GetOldX(), GetOldY()));
			win->SetScreenTile(GetX(), GetY(), GetSpriteNum());
		}
	/*else
		win->SetScreenTile(x, y, 0);

	visible = !visible;
	*/
}

void Cursor::Move(int keynum)
{

	switch (keynum)
	{
	case SDLK_RIGHT:
		moveHelper();
		SetPos(GetX() + 1, GetY());
		break;
	case SDLK_LEFT:
		moveHelper();
		SetPos(GetX() - 1, GetY());
		break;
	case SDLK_UP:
		moveHelper();
		SetPos(GetX(), GetY() - 1);
		break;
	case SDLK_DOWN:
		moveHelper();
		SetPos(GetX(), GetY() + 1);
		break;
	default:
		break;
	}
}