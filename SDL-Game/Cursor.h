#pragma once
#include "Entity.h"
class Cursor :
	public Entity
{
private:
	bool visible = true;
public:
	Cursor(Window* win, int spriteNum, int x = 0, int y = 0);
	~Cursor();

	void Update();
	void Move(int keynum);
};

