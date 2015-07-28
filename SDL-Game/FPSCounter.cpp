#include "FPSCounter.h"
#include <Windows.h>

FPSCounter::FPSCounter()
{
	
}


FPSCounter::~FPSCounter()
{
}

int FPSCounter::frames = 0;
double FPSCounter::starttime = GetTickCount64()/1000;
double FPSCounter::fps = 0.0;

void FPSCounter::checkFPS(void)
{
	frames++;
	ULONGLONG currentTime = GetTickCount64() / 1000;
	if (currentTime - starttime > 0.25 && frames > 10)
	{
		fps = (double)frames / (currentTime-starttime);
		starttime = currentTime;
		frames = 0;
	}
}

double FPSCounter::GetFPS(void)
{
	return fps;
}