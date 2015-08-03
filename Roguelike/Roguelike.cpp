// Roguelike.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <SDL.h>
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>

#include <json\json.h>
#include "Utility.h"
#include "GameController.h"
#include "Entity.h"



int main(int , char *[])
{
	//getting config information
	std::ifstream in("data/config.json");
	Json::Value value;
	int resX = NULL, resY = NULL, levelX = NULL, levelY = NULL, spriteX = NULL, spriteY = NULL;
	in >> value;
	for (Json::Value::iterator it = value.begin(); it != value.end(); it++)
	{
		try
		{
			resX = (*it)["ResX"].asInt();
			resY = (*it)["ResY"].asInt();
			levelX = (*it)["LevelX"].asInt();
			levelY = (*it)["LevelY"].asInt();
			spriteX = (*it)["SpriteX"].asInt();
			spriteY = (*it)["SpriteY"].asInt();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return 1;
		}
	}


	//Passing everything over to game controller
	GameController controller(resX, resY, levelX, levelY, spriteX, spriteY);


	const int TICKS_PER_SECOND = 25;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;

	DWORD next_game_tick = GetTickCount();
	int loops;
	float interpolation;

	bool game_is_running = true;
	while (game_is_running) {

		loops = 0;
		while (GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP) {
			controller.updateGame();

			next_game_tick += SKIP_TICKS;
			loops++;
		}

		controller.displayGame();
	}

    return 0;
}

