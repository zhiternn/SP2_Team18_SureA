
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	static void GetMouseMovement(double& x, double& y);
	static void SetMousePosition(double x, double y);
	static void GetScreenSize(int& x, int& y);
	static bool state2D;

private:

	//Declare a window object
	StopWatch m_timer;
};

#endif