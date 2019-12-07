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
	InputManager(SDL_Window *newWindow) : window(newWindow) { initialize(); }
	~InputManager(){};

	void update(float deltaTime);
	void processInput(SDL_Event windowEvent);

	void processKeyboardUp(SDL_KeyboardEvent keyboardEvent);
	void processKeyboardDown(SDL_KeyboardEvent keyboardEvent);
	void processMouseButton(SDL_MouseButtonEvent mouseButtonEvent);
	void processMouseMovement(SDL_MouseMotionEvent mouseEvent);

	inline bool GetRightClick() { return rightClick; };
	inline bool GetLeftClick() { return leftClick; };
	inline bool GetMiddleClick() { return middleClick; }
	inline bool GetKeyA() { return keyStates["A"]; };
	inline bool GetKeyB() { return keyStates["B"]; };
	inline bool GetKeyC() { return keyStates["C"]; };
	inline bool GetKeyD() { return keyStates["D"]; };
	inline bool GetKeyE() { return keyStates["E"]; };
	inline bool GetKeyF() { return keyStates["F"]; };
	inline bool GetKeyG() { return keyStates["G"]; };
	inline bool GetKeyH() { return keyStates["H"]; };
	inline bool GetKeyI() { return keyStates["I"]; };
	inline bool GetKeyJ() { return keyStates["J"]; };
	inline bool GetKeyK() { return keyStates["K"]; };
	inline bool GetKeyL() { return keyStates["L"]; };
	inline bool GetKeyM() { return keyStates["M"]; };
	inline bool GetKeyN() { return keyStates["N"]; };
	inline bool GetKeyO() { return keyStates["O"]; };
	inline bool GetKeyP() { return keyStates["P"]; };
	inline bool GetKeyQ() { return keyStates["Q"]; };
	inline bool GetKeyR() { return keyStates["R"]; };
	inline bool GetKeyS() { return keyStates["S"]; };
	inline bool GetKeyT() { return keyStates["T"]; };
	inline bool GetKeyU() { return keyStates["U"]; };
	inline bool GetKeyV() { return keyStates["V"]; };
	inline bool GetKeyW() { return keyStates["W"]; };
	inline bool GetKeyX() { return keyStates["X"]; };
	inline bool GetKeyY() { return keyStates["Y"]; };
	inline bool GetKeyZ() { return keyStates["Z"]; };

	inline bool GetKeyLeftShift() { return keyStates["Left Shift"]; };
	inline bool GetKeyRightShift() { return keyStates["Right Shift"]; };
	inline bool GetKeyLeftControl() { return keyStates["Left Control"]; };
	inline bool GetKeyRightControl() { return keyStates["Right Control"]; };
	inline bool GetKeyLeftAlt() { return keyStates["Left Alt"]; };
	inline bool GetKeyRightAlt() { return keyStates["Right Alt"]; };
	inline bool GetKeySpace() { return keyStates["Space"]; };
	inline bool GetKeyTab() { return keyStates["Tab"]; };
	inline bool GetKeyEscape() { return keyStates["Escape"]; };

	SDL_Window *window;

	double xpos, ypos, scroll;

	void GetMouseMovement()
	{
		// glfwGetCursorPos(window, &xpos, &ypos);
	}

	void GetMouseScroll()
	{
	}

	using GP1 = Gamepad::Gamepad<0>;
	ControllerState controller1;
	using GP2 = Gamepad::Gamepad<1>;
	ControllerState controller2;
	using GP3 = Gamepad::Gamepad<2>;
	ControllerState controller3;
	using GP4 = Gamepad::Gamepad<3>;
	ControllerState controller4;

private:
	void initialize()
	{
		// glfwSetCursorPosCallback(window, mouse_callback);
		// glfwSetScrollCallback(window, scroll_callback);
	}

	std::map<std::string, bool> keyStates;
	bool leftClick, rightClick, middleClick;
};