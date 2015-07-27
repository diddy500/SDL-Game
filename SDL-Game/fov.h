#pragma once
class Level;
class Entity;

void fov(int x, int y, Level* lev, Entity* me);

/* Los calculation */
void los(int x0, int y0, int x1, int y1, Level* lev, Entity* me);