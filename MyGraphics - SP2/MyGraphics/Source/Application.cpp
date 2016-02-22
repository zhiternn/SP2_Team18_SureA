#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

#include "SP2.h"
#include "SharedData.h"
#include "mainMenu.h"

GLFWwindow* m_window;
const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame

bool Application::state2D;

//Define an error callback
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

void Application::SetMousePosition(double x, double y)
{
	if (x == 0 && y == 0){
		int sizeX = 0;
		int sizeY = 0;

		glfwGetWindowSize(m_window, &sizeX, &sizeY);

		sizeX = (sizeX / 2) - x;
		sizeY = (sizeY / 2) - y;

		glfwSetCursorPos(m_window, sizeX, sizeY);
	}
	else{
		glfwSetCursorPos(m_window, x, y);
	}
}

void Application::GetMouseMovement(double& x, double& y)
{
	int sizeX = 0;
	int sizeY = 0;

	glfwGetCursorPos(m_window, &x, &y);
	glfwGetWindowSize(m_window, &sizeX, &sizeY);

	x = (sizeX / 2) - x;
	y = (sizeY / 2) - y;
}

void Application::ShowCursor()
{
	glfwSetInputMode(m_window,
		GLFW_CURSOR,
		GLFW_CURSOR_NORMAL
		);
}
void Application::HideCursor()
{
	glfwSetInputMode(m_window,
		GLFW_CURSOR,
		GLFW_CURSOR_HIDDEN
		);
}

void Application::GetScreenSize(int& x, int& y)
{
	glfwGetWindowSize(m_window, &x, &y);
}

Application::Application()
{
}

Application::~Application()
{
}

void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h); //update opengl the new window size
}

void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	//Create a window and create its OpenGL context
	m_window = glfwCreateWindow(1920, 1080, "Computer Graphics :D", NULL, NULL);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	int sizeX = 0;
	int sizeY = 0;
	glfwGetWindowSize(m_window, &sizeX, &sizeY);
	glfwSetCursorPos(m_window, sizeX / 2, sizeY / 2);

	glfwSetInputMode(m_window,
		GLFW_CURSOR,
		GLFW_CURSOR_NORMAL
		);
}

void Application::Run()
{
	//Main Loop
	Scene *scene = new mainMenu();
	scene->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && SharedData::GetInstance()->gameState != SharedData::G_EXIT && !IsKeyPressed(VK_ESCAPE))
	{
		scene->Update(m_timer.getElapsedTime());
		scene->Render();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();

		//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwGetCursorPos(m_window, &SharedData::GetInstance()->m_newX, &SharedData::GetInstance()->m_newY);

		//limit cursor to the resolution of the window
		if (SharedData::GetInstance()->gameState == SharedData::G_MENU) {
			if (SharedData::GetInstance()->m_newX <= 0)
				glfwSetCursorPos(m_window, 0, SharedData::GetInstance()->m_newY);

			if (SharedData::GetInstance()->m_newX >= 1920)
				glfwSetCursorPos(m_window, 1920, SharedData::GetInstance()->m_newY);

			if (SharedData::GetInstance()->m_newY <= 0)
				glfwSetCursorPos(m_window, SharedData::GetInstance()->m_newX, 0);

			if (SharedData::GetInstance()->m_newY >= 1080)
				glfwSetCursorPos(m_window, SharedData::GetInstance()->m_newX, 1080);
		}

        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.   

		if (SharedData::GetInstance()->stateChange) {
			delete scene;
			SharedData::GetInstance()->stateChange = false;
			switch (SharedData::GetInstance()->gameState)
			{
			case SharedData::G_MENU: scene = new mainMenu();
				break;
			case SharedData::G_GAME: scene = new SP2();
				break;
			}
			scene->Init();
		}

	} //Check if the ESC key had been pressed or if the window had been closed
	scene->Exit();
	delete scene;
}

void Application::Exit()
{
	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}
