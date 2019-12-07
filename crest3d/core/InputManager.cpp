#include "InputManager.h"
#include "Debug.h"


void InputManager::processKeyboardDown(SDL_KeyboardEvent keyboardEvent)
{
	keyStates[SDL_GetKeyName(keyboardEvent.keysym.sym)] = true;
}

void InputManager::processKeyboardUp(SDL_KeyboardEvent keyboardEvent)
{
	keyStates[SDL_GetKeyName(keyboardEvent.keysym.sym)] = false;
}


void InputManager::processMouseMovement(SDL_MouseMotionEvent mouseEvent)
{
	xpos = mouseEvent.x;
	ypos = mouseEvent.y;
}

void InputManager::processMouseButton(SDL_MouseButtonEvent mouseButtonEvent)
{
	if(mouseButtonEvent.type == SDL_MOUSEBUTTONDOWN)
	{
		if(mouseButtonEvent.button == SDL_BUTTON_LEFT)
		{
			leftClick = true;
		}
		if (mouseButtonEvent.button == SDL_BUTTON_RIGHT)
		{
			rightClick = true;
		}
		if(mouseButtonEvent.button == SDL_BUTTON_MIDDLE)
		{
			middleClick = true;
		}
	}
	else if(mouseButtonEvent.type == SDL_MOUSEBUTTONUP)
	{
		if (mouseButtonEvent.button == SDL_BUTTON_LEFT)
		{
			leftClick = false;
		}
		if (mouseButtonEvent.button == SDL_BUTTON_RIGHT)
		{
			rightClick = false;
		}
		if (mouseButtonEvent.button == SDL_BUTTON_MIDDLE)
		{
			middleClick = false;
		}
	}
}

void InputManager::update(float deltaTime)
{
	GP1::update();
	if(GP1::isConnected())
	{
		controller1.a_button = GP1::isButtonPressed(Gamepad::Button::A);
		controller1.b_button = GP1::isButtonPressed(Gamepad::Button::B);
		controller1.x_button = GP1::isButtonPressed(Gamepad::Button::X);
		controller1.y_button = GP1::isButtonPressed(Gamepad::Button::Y);

		controller1.up_button = GP1::isButtonPressed(Gamepad::Button::Up);
		controller1.down_button = GP1::isButtonPressed(Gamepad::Button::Down);
		controller1.left_button = GP1::isButtonPressed(Gamepad::Button::Left);
		controller1.right_button = GP1::isButtonPressed(Gamepad::Button::Right);

		controller1.left_x_input = GP1::getLStickPosition().x;
		controller1.left_y_input = GP1::getLStickPosition().y;
		controller1.right_x_input = GP1::getRStickPosition().x;
		controller1.right_y_input = GP1::getRStickPosition().y;

		controller1.right_trigger = GP1::getRTrigger();
		controller1.left_trigger = GP1::getRTrigger();
		controller1.right_bumper = GP1::isButtonPressed(Gamepad::Button::RB);
		controller1.left_bumper = GP1::isButtonPressed(Gamepad::Button::LB);

		controller1.start_button = GP1::isButtonPressed(Gamepad::Button::Start);
		controller1.back_button = GP1::isButtonPressed(Gamepad::Button::Back);

		controller1.left_click = GP1::isButtonPressed(Gamepad::Button::LStick);
		controller1.right_click = GP1::isButtonPressed(Gamepad::Button::RStick);
		// update
	}
	GP2::update();
	if(GP2::isConnected())
	{
		

		controller2.a_button = GP2::isButtonPressed(Gamepad::Button::A);
		controller2.b_button = GP2::isButtonPressed(Gamepad::Button::B);
		controller2.x_button = GP2::isButtonPressed(Gamepad::Button::X);
		controller2.y_button = GP2::isButtonPressed(Gamepad::Button::Y);

		controller2.up_button = GP2::isButtonPressed(Gamepad::Button::Up);
		controller2.down_button = GP2::isButtonPressed(Gamepad::Button::Down);
		controller2.left_button = GP2::isButtonPressed(Gamepad::Button::Left);
		controller2.right_button = GP2::isButtonPressed(Gamepad::Button::Right);

		controller2.left_x_input = GP2::getLStickPosition().x;
		controller2.left_y_input = GP2::getLStickPosition().y;
		controller2.right_x_input = GP2::getRStickPosition().x;
		controller2.right_y_input = GP2::getRStickPosition().y;

		controller2.right_trigger = GP2::getRTrigger();
		controller2.left_trigger = GP2::getRTrigger();
		controller2.right_bumper = GP2::isButtonPressed(Gamepad::Button::RB);
		controller2.left_bumper = GP2::isButtonPressed(Gamepad::Button::LB);

		controller2.start_button = GP2::isButtonPressed(Gamepad::Button::Start);
		controller2.back_button = GP2::isButtonPressed(Gamepad::Button::Back);

		controller2.left_click = GP2::isButtonPressed(Gamepad::Button::LStick);
		controller2.right_click = GP2::isButtonPressed(Gamepad::Button::RStick);
	}
	GP3::update();
	if (GP3::isConnected())
	{
		controller3.a_button = GP3::isButtonPressed(Gamepad::Button::A);
		controller3.b_button = GP3::isButtonPressed(Gamepad::Button::B);
		controller3.x_button = GP3::isButtonPressed(Gamepad::Button::X);
		controller3.y_button = GP3::isButtonPressed(Gamepad::Button::Y);

		controller3.up_button = GP3::isButtonPressed(Gamepad::Button::Up);
		controller3.down_button = GP3::isButtonPressed(Gamepad::Button::Down);
		controller3.left_button = GP3::isButtonPressed(Gamepad::Button::Left);
		controller3.right_button = GP3::isButtonPressed(Gamepad::Button::Right);

		controller3.left_x_input = GP3::getLStickPosition().x;
		controller3.left_y_input = GP3::getLStickPosition().y;
		controller3.right_x_input = GP3::getRStickPosition().x;
		controller3.right_y_input = GP3::getRStickPosition().y;

		controller3.right_trigger = GP3::getRTrigger();
		controller3.left_trigger = GP3::getRTrigger();
		controller3.right_bumper = GP3::isButtonPressed(Gamepad::Button::RB);
		controller3.left_bumper = GP3::isButtonPressed(Gamepad::Button::LB);

		controller3.start_button = GP3::isButtonPressed(Gamepad::Button::Start);
		controller3.back_button = GP3::isButtonPressed(Gamepad::Button::Back);

		controller3.left_click = GP3::isButtonPressed(Gamepad::Button::LStick);
		controller3.right_click = GP3::isButtonPressed(Gamepad::Button::RStick);
	}
	GP4::update();
	if (GP4::isConnected())
	{
		controller4.a_button = GP4::isButtonPressed(Gamepad::Button::A);
		controller4.b_button = GP4::isButtonPressed(Gamepad::Button::B);
		controller4.x_button = GP4::isButtonPressed(Gamepad::Button::X);
		controller4.y_button = GP4::isButtonPressed(Gamepad::Button::Y);

		controller4.up_button = GP4::isButtonPressed(Gamepad::Button::Up);
		controller4.down_button = GP4::isButtonPressed(Gamepad::Button::Down);
		controller4.left_button = GP4::isButtonPressed(Gamepad::Button::Left);
		controller4.right_button = GP4::isButtonPressed(Gamepad::Button::Right);

		controller4.left_x_input = GP4::getLStickPosition().x;
		controller4.left_y_input = GP4::getLStickPosition().y;
		controller4.right_x_input = GP4::getRStickPosition().x;
		controller4.right_y_input = GP4::getRStickPosition().y;

		controller4.right_trigger = GP4::getRTrigger();
		controller4.left_trigger = GP4::getRTrigger();
		controller4.right_bumper = GP4::isButtonPressed(Gamepad::Button::RB);
		controller4.left_bumper = GP4::isButtonPressed(Gamepad::Button::LB);

		controller4.start_button = GP4::isButtonPressed(Gamepad::Button::Start);
		controller4.back_button = GP4::isButtonPressed(Gamepad::Button::Back);

		controller4.left_click = GP4::isButtonPressed(Gamepad::Button::LStick);
		controller4.right_click = GP4::isButtonPressed(Gamepad::Button::RStick);
	}
	
}


void InputManager::processInput(SDL_Event windowEvent)
{
	switch (windowEvent.type)
	{
	case SDL_KEYDOWN:
		// Debug::Message<InputManager>("Key press detected");
		processKeyboardDown(windowEvent.key);
		break;
	case SDL_KEYUP:
		// Debug::Message<InputManager>("Key release detected");
		processKeyboardUp(windowEvent.key);
		break;
	case SDL_MOUSEMOTION:
		// Debug::Message<InputManager>("Mouse movement detected");
		processMouseMovement(windowEvent.motion);
		break;
	case SDL_MOUSEBUTTONDOWN:
		processMouseButton(windowEvent.button);
		break;
		// Debug::Message<InputManager>("Mouse button pressed");
	case SDL_MOUSEBUTTONUP:
		processMouseButton(windowEvent.button);
		break;
	}
}
