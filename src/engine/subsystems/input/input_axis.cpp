#include "engine/subsystems/input/input_axis.h"
#include "engine/subsystems/input/input_subsystem.h"

#include <cassert>

InputAxis::InputAxis(InputSubSystem * input)
	: input(input)
{
}

void InputAxis::addKeyboardKey(Keyboard::Key key, float value)
{
	keyboardKeys.push_back({ key, value });
}

void InputAxis::addGamepadAxis(Gamepad::Axis axis, float value, unsigned int gamepadIndex)
{
	gamepadAxes.push_back({ axis, value, gamepadIndex });
}

void InputAxis::addMouseAxis(Mouse::Axis axis, float value)
{
	mouseAxes.push_back({ axis, value });
}

const std::vector<InputAxis::KeyboardKey>& InputAxis::getKeyboardKeys() const
{
	return keyboardKeys;
}

const std::vector<InputAxis::GamepadAxis>& InputAxis::getGamepadAxes() const
{
	return gamepadAxes;
}

const std::vector<InputAxis::MouseAxis>& InputAxis::getMouseAxes() const
{
	return mouseAxes;
}

float InputAxis::getAxisValue() const
{
	assert(input != nullptr);
	return input->getAxisValue(this);
}
