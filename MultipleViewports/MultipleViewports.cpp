// MultipleViewports.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include "Core.h"
#include "Setup_texShaders.h"


Abj myAbj;

int main(int argc, char *argv[])
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

	GLuint VAO, VBO_P;

	glCreateBuffers(1, &VBO_P);
	glNamedBufferData(VBO_P, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	vector<glm::vec3> triP;
	triP.push_back({ -.5f, -.5f, 0.f });
	triP.push_back({ .5f, -.5f, 0.f });
	triP.push_back({ 0.f, .5f, 0.f });

	glNamedBufferData(VBO_P, triP.size() * sizeof(glm::vec3), &triP[0], GL_STATIC_DRAW);

	glCreateVertexArrays(1, &VAO);
	glEnableVertexArrayAttrib(VAO, 0);
	glVertexArrayVertexBuffer(VAO, 0, VBO_P, 0, sizeof(glm::vec3));
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);

	proInit();

	do
	{
		glClearColor(0.f, 0.f, 0.f, 0.f);
		glViewport(0, 0, myAbj.width, myAbj.height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram2("pTri");
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(myAbj.GLFWwin);
		glfwPollEvents();
	}

	while
		//(!myAbj.quitTgl && glfwWindowShouldClose(myAbj.GLFWwin) == 0);
		(glfwWindowShouldClose(myAbj.GLFWwin) == 0);

	return 0;
}
