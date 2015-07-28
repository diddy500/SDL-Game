#pragma once
class FPSCounter
{
private:

	static int frames;
	static double starttime;
	static double fps;
public:
	FPSCounter();
	~FPSCounter();

	void checkFPS(void);
	double GetFPS(void);

};

