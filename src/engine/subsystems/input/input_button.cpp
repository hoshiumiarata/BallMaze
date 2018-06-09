#include "engine/subsystems/input/input_button.h"
#include "engine/subsystems/input/input_subsystem.h"

#include <cassert>

InputButton::InputButton(InputSubSystem* input)
	: input(input)
{
}

void InputButton::addKeyboardKey(Keyboard::Key key)
{
	keyboardKeys.push_back(key);
}

const std::vector<Keyboard::Key>& InputButton::getKeyboardKeys() const
{
	return keyboardKeys;
}

bool InputButton::isPressed() const
{
	assert(input != nullptr);
	return input->isPressed(this);
}

bool InputButton::isReleased() const
{
	return !isPressed();
}
