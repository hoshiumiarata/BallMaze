#pragma once

#include "keyboard.h"
#include "gamepad.h"
#include "mouse.h"

#include <vector>

class InputSubSystem;

class InputAxis
{
public:
	InputAxis() = default;
	explicit InputAxis(InputSubSystem* input);

	struct KeyboardKey
	{
		Keyboard::Key key;
		float value;
	};

	struct GamepadAxis
	{
		Gamepad::Axis axis;
		float value;
		unsigned int gamepadIndex;
	};
	
	struct MouseAxis
	{
		Mouse::Axis axis;
		float value;
	};

	void addKeyboardKey(Keyboard::Key key, float value = 1.0f);
	void addGamepadAxis(Gamepad::Axis axis, float value = 1.0f, unsigned int gamepadIndex = 0);
	void addMouseAxis(Mouse::Axis axis, float value = 1.0f);
	const std::vector<KeyboardKey>& getKeyboardKeys() const;
	const std::vector<GamepadAxis>& getGamepadAxes() const;
	const std::vector<MouseAxis>& getMouseAxes() const;

	float getAxisValue() const;
private:
	std::vector<KeyboardKey> keyboardKeys;
	std::vector<GamepadAxis> gamepadAxes;
	std::vector<MouseAxis> mouseAxes;

	InputSubSystem* input = nullptr;
};