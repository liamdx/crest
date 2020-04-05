#pragma once
#include "Common.h"
#include "Gamepad.hpp"

struct ControllerState
{
	float left_x_input;
	float left_y_input;
	float right_x_input;
	float right_y_input;
	float left_trigger;
	float right_trigger;
	bool left_bumper;
	bool right_bumper;
	bool up_button;
	bool down_button;
	bool left_button;
	bool right_button;
	bool start_button;
	bool back_button;
	bool a_button;
	bool b_button;
	bool x_button;
	bool y_button;
	bool left_click;
	bool right_click;
};

class InputManager
{
public:
	InputManager(GLFWwindow* newWindow) : window(newWindow) { initialize(); }
	~InputManager(){};

	void update(float deltaTime);
	void processInput();

	GLFWwindow* window;

	double xpos, ypos, scroll;

	using GP1 = Gamepad::Gamepad<0>;
	ControllerState controller1;
	using GP2 = Gamepad::Gamepad<1>;
	ControllerState controller2;
	using GP3 = Gamepad::Gamepad<2>;
	ControllerState controller3;
	using GP4 = Gamepad::Gamepad<3>;
	ControllerState controller4;


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

	 
	static void mouse_callback(GLFWwindow* window, double _xpos, double _ypos)
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

	bool leftClick, rightClick, middleClick;
};