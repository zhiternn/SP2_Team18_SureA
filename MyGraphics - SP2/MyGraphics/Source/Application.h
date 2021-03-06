
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
	static void SetMousePosition(double x = 0, double y = 0);
	static void GetScreenSize(int& x, int& y);
	static bool state2D;
	static void ShowCursor();
	static void HideCursor();

	static double mouseWheelX;
	static double mouseWheelY;
	static int width;
	static int height;

private:

	//Declare a window object
	StopWatch m_timer;
};

#endif