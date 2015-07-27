#include "fov.h"
#include <cmath>
#include "Level.h"
#include "Entity.h"
#include "Player.h"
#include "NPC.h"

const int radius = 100;
void fov(int x, int y, Level* lev, Entity* me)
{
	int i, j;
	for (i = -(int)radius; i <= radius; i++) //iterate out of map bounds as well
		for (j = -(int)radius; j <= radius; j++)
			if (i * i + j * j < radius * radius)
				los(x, y, i, j, lev, me);


}

void los(int x0, int y0, int x1, int y1, Level* lev, Entity* me)
// By taking source by reference, litting can be done outside of this function which would be better made generic.
{
	int sx, sy, xnext, ynext, dx, dy;
	double denom;
	dx = x1 - x0;
	dy = y1 - y0;
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	// sx and sy are switches that enable us to compute the LOS in a single quarter of x/y plan
	xnext = x0;
	ynext = y0;
	denom = sqrt(dx * dx + dy * dy);
	while (xnext != x1 || ynext != y1)
	{
		// check map bounds here if needed
		if (!lev->GetBackgroundTile(xnext,ynext) || !lev->GetBackgroundTile(xnext,ynext)->isWalkable) // or any equivalent
		{

			if (Player* play = dynamic_cast<Player*> (me))
				play->SeeTile(xnext, ynext);
			//else if (NPC* npc = dynamic_cast<NPC*> (me))
				
			return;
		}
		// Line-to-point distance formula < 0.5
		if (abs(dy * (xnext - x0 + sx) - dx * (ynext - y0)) / denom < 0.5f)
			xnext += sx;
		else if (abs(dy * (xnext - x0) - dx * (ynext - y0 + sy)) / denom < 0.5f)
			ynext += sy;
		else
		{
			xnext += sx;
			ynext += sy;
		}
	}
	if (Player* play = dynamic_cast<Player*> (me))
		play->SeeTile(x1, y1);
}