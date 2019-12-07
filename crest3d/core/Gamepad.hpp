#pragma once

#pragma comment(lib, "Xinput9_1_0.lib")

#if defined( _M_X64 )
#define _AMD64_
#elif defined ( _M_IX86 )
#define _X86_
#elif defined( _M_ARM )
#define _ARM_
#endif

#define NOMINMAX // Suppresses the 'min' and 'max' macros in Windef.h (for the love of God, Microsoft, why use macros that break the standard??)

#include <functional>
#include <Xinput.h>
#include <Windows.h>
#include <algorithm>
#include <limits>
#include <cstring>
#include <cmath>
#include <thread>
#include <chrono>
#include <atomic>
#include <type_traits>
#include <utility>
using namespace std;

#ifdef max
#error "The macro 'max' is defined, which breaks the code below. Please make sure that 'NOMINMAX' is defined before including any Windows-related header files!"
#else

#define GP_INDEX_ASSERT	static_assert((index >= 0) && (index <= 3), "Gamepad index out of range! Valid range is [0,3].")

namespace Gamepad {

	struct vec2 {
		vec2() {}
		vec2(float _x, float _y) : x{ _x }, y{ _y } {}
		float x{ 0.0f }, y{ 0.0f };
	};

	// These values represent the buttons on a gamepad using a 360-style naming scheme.
	enum Button {
		A = XINPUT_GAMEPAD_A,
		B = XINPUT_GAMEPAD_B,
		X = XINPUT_GAMEPAD_X,
		Y = XINPUT_GAMEPAD_Y,
		Up = XINPUT_GAMEPAD_DPAD_UP,
		Down = XINPUT_GAMEPAD_DPAD_DOWN,
		Left = XINPUT_GAMEPAD_DPAD_LEFT,
		Right = XINPUT_GAMEPAD_DPAD_RIGHT,
		LB = XINPUT_GAMEPAD_LEFT_SHOULDER,
		RB = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		LStick = XINPUT_GAMEPAD_LEFT_THUMB,
		RStick = XINPUT_GAMEPAD_RIGHT_THUMB,
		Start = XINPUT_GAMEPAD_START,
		Back = XINPUT_GAMEPAD_BACK
	};

	/*
	template <typename T, enable_if_t<is_arithmetic<T>::value, int> = 0>
	static T clamp(const T& value, const T& minimum, const T& maximum) noexcept {
		return max(min(value, maximum), minimum);
	} */

	static float magnitude(const vec2& a) { return sqrtf(a.x * a.x + a.y * a.y); }

	/*
	This is the class that lets you interface with a gamepad.
	The template argument is an index that specifies which gamepad in the system the class instance will access.
	This index has to be a compile-time constant!
	*/
	template <int index>
	class Gamepad {
		GP_INDEX_ASSERT;
	public:

		/*
		Sets a function to be called each time a button is pressed.
		The function will be given a 'Gamepad::Button' argument that corresponds with the button in question.
		*/
		static void setButtonDownCallback(function<void(Button)> fn) { buttonDownCallback = fn; }

		/*
		Sets a function to be called each time a button is released.
		The function will be given a 'Gamepad::Button' argument that corresponds with the button in question.
		*/
		static void setButtonUpCallback(function<void(Button)> fn) { buttonUpCallback = fn; }

		/*
		Fetches the gamepad hardware and updates the object's internal state accordingly.
		Every method that returns information about the gamepad's state will operate on data retrieved by the last call to this function.
		*/
		static void update() {
			XINPUT_STATE newGpState;
			memset(&newGpState, 0x0, sizeof(newGpState));
			connected = (XInputGetState(index, &newGpState) == ERROR_SUCCESS);
			auto buttonState = gpState.exchange(newGpState).Gamepad.wButtons;
			if (buttonState != newGpState.Gamepad.wButtons) {
				auto stateDiff = static_cast<decltype(buttonState)>(buttonState ^ newGpState.Gamepad.wButtons);
				for (WORD i{ 0x1 };; i <<= 0x1) {
					if (stateDiff & 0x1) {
						if (buttonState & 0x1) {
							if (buttonUpCallback)
								buttonUpCallback(static_cast<Button>(i));
						}
						else {
							if (buttonDownCallback)
								buttonDownCallback(static_cast<Button>(i));
						}
					}
					if (i == 0x8000) break;
					else {
						stateDiff >>= 0x1;
						buttonState >>= 0x1;
					}
				}
			}
		}

		/*
		Indicates if the gamepad is connected or not. This should be checked before fetching any data.
		*/
		static bool isConnected() noexcept { return connected.load(); }

		/*
		Returns the current state of the specified button.
		*/
		static bool isButtonPressed(Button b) noexcept { return (gpState.load().Gamepad.wButtons & b); }

		/*
		Returns a bitmask representing the current state of buttons.
		To retrive individual button states, perform bitwise AND operations with members of the 'Gamepad::Button' enum.
		*/
		static auto getButtonStateMask() noexcept { return gpState.load().Gamepad.wButtons; }

		/*
		Returns the position of the left analog stick. '.x' and '.y' are in the range [-1.0f, 1.0f].
		*/
		static vec2 getLStickPosition() noexcept {
			auto gamepadObject = gpState.load().Gamepad;
			vec2 dirVector{
				static_cast<float>(gamepadObject.sThumbLX) / static_cast<float>(numeric_limits<decltype(gamepadObject.sThumbLX)>::max()),
				static_cast<float>(gamepadObject.sThumbLY * (invertLSY ? -1 : 1)) / static_cast<float>(numeric_limits<decltype(gamepadObject.sThumbLY)>::max()) };
			auto len = magnitude(dirVector);
			if (len < stickDeadzoneLow) { return { 0.0f, 0.0f }; }
			else {
				auto scale = min(1.0f, (len - stickDeadzoneLow) / (1.0f - stickDeadzoneHigh - stickDeadzoneLow)) / len;
				return{ dirVector.x * scale, dirVector.y * scale };
			};
		}

		/*
		Returns the position of the right analog stick. '.x' and '.y' are in the range [-1.0f, 1.0f].
		*/
		static vec2 getRStickPosition() noexcept {
			auto gamepadObject = gpState.load().Gamepad;
			vec2 dirVector{
				static_cast<float>(gamepadObject.sThumbRX) / static_cast<float>(numeric_limits<decltype(gamepadObject.sThumbRX)>::max()),
				static_cast<float>(gamepadObject.sThumbRY * (invertLSY ? -1 : 1)) / static_cast<float>(numeric_limits<decltype(gamepadObject.sThumbRY)>::max()) };
			auto len = magnitude(dirVector);
			if (len < stickDeadzoneLow) { return{ 0.0f, 0.0f }; }
			else {
				auto scale = min(1.0f, (len - stickDeadzoneLow) / (1.0f - stickDeadzoneHigh - stickDeadzoneLow)) / len;
				return{ dirVector.x * scale, dirVector.y * scale };
			};
		}

		/*
		Returns the position of the left analog stick. '.x' and '.y' are in the range [-1.0f, 1.0f].
		This function returns raw values, meaning they are not affected by deadzones, normalized to a circle, or anything like that.
		The optional inversion of the Y axis is still applied however!
		*/
		static vec2 getLStickPositionRaw() noexcept {
			auto gamepadObject = gpState.load().Gamepad;
			return {
				static_cast<float>(gamepadObject.sThumbLX) / static_cast<float>(numeric_limits<decltype(gamepadObject.sThumbLX)>::max()),
				static_cast<float>(gamepadObject.sThumbLY * (invertLSY ? -1 : 1)) / static_cast<float>(numeric_limits<decltype(gamepadObject.sThumbLY)>::max())
			};
		}

		/*
		Returns the position of the right analog stick. '.x' and '.y' are in the range [-1.0f, 1.0f].
		This function returns raw values, meaning they are not affected by deadzones, normalized to a circle, or anything like that.
		The optional inversion of the Y axis is still applied however!
		*/
		static vec2 getRStickPositionRaw() noexcept {
			auto gamepadObject = gpState.load().Gamepad;
			return {
				static_cast<float>(gamepadObject.sThumbRX) / static_cast<float>(numeric_limits<decltype(gamepadObject.sThumbRX)>::max()),
				static_cast<float>(gamepadObject.sThumbRY * (invertLSY ? -1 : 1)) / static_cast<float>(numeric_limits<decltype(gamepadObject.sThumbRY)>::max())
			};
		}

		/*
		Returns the position of the left trigger in the range [0.0f, 1.0f].
		*/
		static float getLTrigger() noexcept {
			auto x = gpState.load().Gamepad.bLeftTrigger;
			auto xf = static_cast<float>(x) / static_cast<float>(numeric_limits<decltype(x)>::max());
			return (xf > triggerDeadzoneLow) ? min(1.0f, (xf - triggerDeadzoneLow) / (1.0f - triggerDeadzoneHigh - triggerDeadzoneLow)) : 0.0f;
		}

		/*
		Returns the position of the right trigger in the range [0.0f, 1.0f].
		*/
		static float getRTrigger() noexcept {
			auto x = gpState.load().Gamepad.bRightTrigger;
			auto xf = static_cast<float>(x) / static_cast<float>(numeric_limits<decltype(x)>::max());
			return (xf > triggerDeadzoneLow) ? min(1.0f, (xf - triggerDeadzoneLow) / (1.0f - triggerDeadzoneHigh - triggerDeadzoneLow)) : 0.0f;
		}

		/*
		Vibrates the gamepad. 'L' and 'R' define the intensity for the left and right motors respectively.
		Both arguments should be in the range [0.0f, 1.0f]. 0.0f turns vibrations off on the corresponding motor.
		*/
		static void vibrate(float L, float R) {
			//L = clamp(L, 0.0f, 1.0f);
			//R = clamp(R, 0.0f, 1.0f);
			XINPUT_VIBRATION vState;
			memset(&vState, 0x0, sizeof(decltype(vState)));
			vState.wLeftMotorSpeed = L * static_cast<float>(numeric_limits<decltype(XINPUT_VIBRATION::wLeftMotorSpeed)>::max()) + 0.4999f;
			vState.wRightMotorSpeed = L * static_cast<float>(numeric_limits<decltype(XINPUT_VIBRATION::wRightMotorSpeed)>::max()) + 0.4999f;
			XInputSetState(index, &vState);
		}

		/*
		Sets whether or not the Y-axis of the left analog stick is inverted when retrieving its state.
		*/
		static void setInvertLStickY(bool b) noexcept { invertLSY = b; }

		/*
		Sets whether or not the Y-axis of the right analog stick is inverted when retrieving its state.
		*/
		static void setInvertRStickY(bool b) noexcept { invertRSY = b; }

		/*
		Sets the deadzones for the analog sticks.
		'low' is the inner deadzone, 'high' is the outer deadzone.
		Both values should be in the range [0.0f, 1.0f].
		*/
		static void setStickDeadzones(float low, float high) {
			stickDeadzoneLow = low;
			stickDeadzoneHigh = high;
		}

		/*
		Returns the current inner and outer deadzones used on the analog sticks.
		The first value is the inner deadzone, second value is the outer deadzone.
		*/
		static pair<float, float> getStickDeadzones() {
			return { stickDeadzoneLow, stickDeadzoneHigh };
		}

		/*
		Sets the deadzones for the triggers.
		'low' is the inner deadzone, 'high' is the outer deadzone.
		Both values should be in the range [0.0f, 1.0f].
		*/
		static void setTriggerDeadzones(float low, float high) {
			triggerDeadzoneLow = low;
			triggerDeadzoneHigh = high;
		}

		/*
		Returns the current inner and outer deadzones used on the triggers.
		The first value is the inner deadzone, second value is the outer deadzone.
		*/
		static pair<float, float> getTriggerDeadzones() {
			return{ triggerDeadzoneLow, triggerDeadzoneHigh };
		}

	private:
		static function<void(Button)> buttonDownCallback;
		static function<void(Button)> buttonUpCallback;
		static atomic<XINPUT_STATE> gpState;
		static atomic<bool> connected;
		static bool invertLSY;
		static bool invertRSY;
		static float triggerDeadzoneLow;
		static float triggerDeadzoneHigh;
		static float stickDeadzoneLow;
		static float stickDeadzoneHigh;
	};

	template <int index>
	function<void(Button)> Gamepad<index>::buttonDownCallback;
	template <int index>
	function<void(Button)> Gamepad<index>::buttonUpCallback;
	template <int index>
	atomic<XINPUT_STATE> Gamepad<index>::gpState;
	template <int index>
	atomic<bool> Gamepad<index>::connected = false;
	template <int index>
	bool Gamepad<index>::invertLSY = false;
	template <int index>
	bool Gamepad<index>::invertRSY = false;
	template <int index>
	float Gamepad<index>::triggerDeadzoneLow = 0.0f;
	template <int index>
	float Gamepad<index>::triggerDeadzoneHigh = 0.0f;
	template <int index>
	float Gamepad<index>::stickDeadzoneLow = 0.1f;
	template <int index>
	float Gamepad<index>::stickDeadzoneHigh = 0.0f;

	/*
	Constructing an object of this type will spun off a thread that will update
	the gamepad specified in the template argument (index) at regular intervals.
	WARNING: updating a gamepad from a separate thread means that the button
	up/down callbacks will be issued from this other thread as well. Make sure
	that your callback handler functions are thread safe!
	*/
	template <int index>
	class UpdaterThread {
		GP_INDEX_ASSERT;
	public:
		using fseconds = chrono::duration<double, ratio<1, 1>>;
		using fseconds = chrono::duration<double, ratio<1, 1>>;
		UpdaterThread(fseconds interval) {
			if (t.joinable()) return;

			t = thread([interval]() {
				while (run) {
					auto t0 = chrono::high_resolution_clock::now();
					Gamepad<index>::update();
					auto t1 = chrono::high_resolution_clock::now();
					this_thread::sleep_for(interval - fseconds{ t1 - t0 });
				}
				});
		}

		/*
		Indicates if the updater thread is running.
		*/
		bool isRunning() const noexcept { return t.joinable(); }

		~UpdaterThread() {
			run = false;
			t.join();
		}

		UpdaterThread(const UpdaterThread<index>&) = delete;
		UpdaterThread(UpdaterThread<index>&&) = delete;
		UpdaterThread& operator=(const UpdaterThread<index>&) = delete;
		UpdaterThread& operator=(UpdaterThread<index>&&) = delete;
	private:
		static atomic<bool> run;
		static thread t;
	};

	template <int index>
	atomic<bool> UpdaterThread<index>::run = true;
	template <int index>
	thread UpdaterThread<index>::t;
}

#undef GP_INDEX_ASSERT

#endif /* defined(max) */