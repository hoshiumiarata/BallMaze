#pragma once

#include "keyboard.h"
#include "gamepad.h"
#include "mouse.h"

#include <vector>

class InputSubSystem;

class InputButton
{
public:
	InputButton() = default;
	explicit InputButton(InputSubSystem* input);

	void addKeyboardKey(Keyboard::Key key);
	const std::vector<Keyboard::Key>& getKeyboardKeys() const;

	bool isPressed() const;
	bool isReleased() const;
private:
	std::vector<Keyboard::Key> keyboardKeys;

	InputSubSystem* input = nullptr;
};