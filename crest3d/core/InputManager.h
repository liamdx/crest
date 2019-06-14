#pragma once
#include "Common.h"

class InputManager {

public:

	InputManager(GLFWwindow* newWindow) : window(newWindow) { initialize(); }

	~InputManager() {};



	bool GetRightClick()
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}

	};

	bool GetLeftClick()
	{
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	bool GetKeyW()
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool GetKeyR()
	{
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool GetKeyS()
	{
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	bool GetKeyA()
	{
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	bool GetKeyD()
	{
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};
	bool GetKeyEsc()
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool GetKeyQ()
	{
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool GetKeyE()
	{
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool GetKeyF()
	{
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	bool GetKeyLeftShift()
	{
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		{
			return true;
		}
		else
		{
			return false;
		}
	};

	GLFWwindow* window;

	double xpos, ypos, scroll;

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{

	}

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
	{
	}

	void GetMouseMovement()
	{
		glfwGetCursorPos(window, &xpos, &ypos);
	}

	void GetMouseScroll()
	{
	}

private:
	void initialize()
	{
		glfwSetCursorPosCallback(window, mouse_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}
};