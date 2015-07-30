#include "FPSCounter.h"
#include "SheetEnum.h"

FPSCounter::FPSCounter()
{
	frames = 0;
	starttime = GetTickCount64() / 1000;
	fps = 0;
}


FPSCounter::~FPSCounter()
{
}



void FPSCounter::checkFPS(void)
{
	frames++;
	ULONGLONG currentTime = GetTickCount64() / 1000;
	if (currentTime - starttime > 0.25 && frames > 10)
	{
		fps = frames / (currentTime-starttime);
		starttime = currentTime;
		frames = 0;
	}
}

std::array<int,2> FPSCounter::GetFPS(void)
{
	
	int fps1 = static_cast<int>(fps / 10);
	int fps2 = static_cast<int>(fps % 10);

	switch (fps1)
	{
	case 0:
		fps1 = NUM_0;
		break;
	case 1:
		fps1 = NUM_1;
		break;
	case 2:
		fps1 = NUM_2;
		break;
	case 3:
		fps1 = NUM_3;
		break;
	case 4:
		fps1 = NUM_4;
		break;
	case 5:
		fps1 = NUM_5;
		break;
	case 6:
		fps1 = NUM_6;
		break;
	case 7:
		fps1 = NUM_7;
		break;
	case 8:
		fps1 = NUM_8;
		break;
	case 9:
		fps1 = NUM_9;
		break;

	}
	switch (fps2)
	{
	case 0:
		fps2 = NUM_0;
		break;
	case 1:
		fps2 = NUM_1;
		break;
	case 2:
		fps2 = NUM_2;
		break;
	case 3:
		fps2 = NUM_3;
		break;
	case 4:
		fps2 = NUM_4;
		break;
	case 5:
		fps2 = NUM_5;
		break;
	case 6:
		fps2 = NUM_6;
		break;
	case 7:
		fps2 = NUM_7;
		break;
	case 8:
		fps2 = NUM_8;
		break;
	case 9:
		fps2 = NUM_9;
		break;

	}
	return std::array<int, 2>  { fps1,fps2 };
}