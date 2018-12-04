// MultipleViewports.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "pch.h"
//#include <iostream>
#include "Core.h"

Abj myAbj;

int main()
{
    std::cout << "Hello World!\n"; 

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); //
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//glfwWindowHint(GLFW_DECORATED, GL_FALSE); //

	/* WIDTH / HEIGHT */
	myAbj.monitorX = 1920;
	myAbj.monitorY = 1080;

	myAbj.width = 1280;
	myAbj.height = 720;

	myAbj.winPosGlobal = glm::ivec2(0, 0); //

	//CENTER
	int posHalfL = myAbj.width / 2;
	int posHalfU = myAbj.height / 2;
	int posHalfMonL = myAbj.monitorX / 2;
	int posHalfMonU = myAbj.monitorY / 2;

	myAbj.winPosGlobal = glm::ivec2(posHalfMonL - posHalfL, posHalfMonU - posHalfU); //

	myAbj.GLFWwin = glfwCreateWindow(myAbj.width, myAbj.height, "Multiple Viewports", 0, 0); //windowed
	glfwSetWindowPos(myAbj.GLFWwin, myAbj.winPosGlobal.x, myAbj.winPosGlobal.y);

	glfwMakeContextCurrent(myAbj.GLFWwin);
	glewExperimental = 1;
	glewInit();
	glfwSetInputMode(myAbj.GLFWwin, GLFW_STICKY_KEYS, GL_TRUE);
	//glfwSetInputMode(myAbj.GLFWwin, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(myAbj.GLFWwin, GLFW_CURSOR, GLFW_CURSOR_NORMAL);


	glfwFocusWindow(myAbj.GLFWwin);

	do
	{
		glfwSwapBuffers(myAbj.GLFWwin);
		glfwPollEvents();
	}

	while
		//(!myAbj.quitTgl && glfwWindowShouldClose(myAbj.GLFWwin) == 0);
		(glfwWindowShouldClose(myAbj.GLFWwin) == 0);

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
