#include "stdafx.h"
#include "GameController.h"


GameController::GameController(const int resX, const int resY, const int levelWidth, const int levelHeight, const int spriteWidth, const int spriteHeight) : levelTiles(levelWidth, levelHeight), screen(resX, resY), console(resX / 5, resY)
{
}

GameController::~GameController()
{
}
