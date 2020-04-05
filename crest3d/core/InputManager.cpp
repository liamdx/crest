#include "InputManager.h"
#include "Debug.h"


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
	
}


void InputManager::processInput()
{
	
}
