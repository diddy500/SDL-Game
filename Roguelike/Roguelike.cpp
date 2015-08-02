// Roguelike.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Utility.h"
#include "Entity.h"
#include <SDL.h>


int main(int , char *[])
{
	Entity ent("ID", 0, 0, Point(1, 1), 10, 10, 10, 10, false);
	ent.Move(NORTH);


    return 0;
}

