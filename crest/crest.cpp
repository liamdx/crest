// crest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//
#include "CrestMath.h"

int main()
{

    std::cout << "Hello World!\n"; 
	Vector3* a = new Vector3(1, 2, 3);
	Vector3* b = new Vector3(1, 5, 7);

	float dotResult = a->dot(*b);

	std::cout << "Dot results between a = (1,2,3) b = (1,5,7) = " << dotResult << std::endl;

	Matrix4 ma = Matrix4(3, 5, 7, 8, 1, 2, 8, 7, 4, 5, 3, -2, 1, 6, 7, 9);
	Matrix4 mb = Matrix4(2, 8, 6, 9, 3, -5, 6, 7, 1, 4, 9, -3, 10, -2, 5, 2);

	ma = ma * mb;

	ma.Print();


	float deltaTime = 0.0;
	float lastFrame = 0.0;

	//DEBUG
	int  success;
	char infoLog[512];
	//GL initialisation
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(1280.0, 720.0, "Crest", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "failed to initalise glew" << std::endl;
	}

	

	// YSE::System().init();

	//Enable depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glfwSwapInterval(0);

	//Mouse input handle

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	
	while (!glfwWindowShouldClose(window))
	{
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

