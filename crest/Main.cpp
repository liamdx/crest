// crest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//
#include "Shader.h"

int main() {

	std::cout << "Hello World!\n";


	float deltaTime = 0.0;
	float lastFrame = 0.0;

	//DEBUG
	int success;
	char infoLog[512];
	//GL initialisation
	GLFWwindow * window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280.0, 720.0, "Crest", NULL, NULL);

	if (!window) {
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "failed to initalise glew" << std::endl;
	}

	// YSE::System().init();

	//Enable depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSwapInterval(0);

	//Mouse input handle

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	while (!glfwWindowShouldClose(window)) {
		//Engine time
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glEnable(GL_DEPTH_TEST);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		/* Poll for and process events */
		glfwPollEvents();

	}

}