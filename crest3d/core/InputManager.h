#pragma once
#include "Common.h"

class InputManager {
public:

	InputManager(SDL_Window* newWindow) : window(newWindow) { initialize(); }

	~InputManager() {};

	void processInput(SDL_Event windowEvent);

	void processKeyboardUp(SDL_KeyboardEvent keyboardEvent);
	void processKeyboardDown(SDL_KeyboardEvent keyboardEvent);
	void processMouseButton(SDL_MouseButtonEvent mouseButtonEvent);
	void processMouseMovement(SDL_MouseMotionEvent mouseEvent);

	bool GetRightClick()
	{
		return rightClick;
	};

	bool GetLeftClick()
	{
		return leftClick;
	};
	bool GetMiddleClick()
	{
		return middleClick;
	}
	bool GetKeyW()
	{
		return keyStates["W"];
	};

	bool GetKeyR()
	{
		return keyStates["W"];
	}

	bool GetKeyS()
	{
		return keyStates["S"];
	};
	bool GetKeyA()
	{
		return keyStates["A"];
	};
	bool GetKeyD()
	{
		return keyStates["D"];
	};
	bool GetKeyEsc()
	{
		return keyStates["Escape"];
	};

	bool GetKeyQ()
	{
		return keyStates["Q"];
	};

	bool GetKeyE()
	{
		return keyStates["E"];
	};

	bool GetKeyF()
	{
		return keyStates["F"];
	};

	bool GetKeyLeftShift()
	{
		return keyStates["Left Shift"];
	};

	SDL_Window* window;

	double xpos, ypos, scroll;


	void GetMouseMovement()
	{
		// glfwGetCursorPos(window, &xpos, &ypos);
	}

	void GetMouseScroll()
	{
	}

private:
	void initialize()
	{
		// glfwSetCursorPosCallback(window, mouse_callback);
		// glfwSetScrollCallback(window, scroll_callback);
	}

	std::map<std::string, bool> keyStates;
	bool leftClick, rightClick, middleClick;
};