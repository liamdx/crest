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
