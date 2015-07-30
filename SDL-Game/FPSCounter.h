#pragma once
#include <array>
#include <Windows.h>

class FPSCounter
{
private:

	ULONGLONG frames;
	ULONGLONG starttime;
	ULONGLONG fps;
public:
	FPSCounter();
	~FPSCounter();

	void checkFPS(void);
	std::array<int, 2> GetFPS(void);

};

