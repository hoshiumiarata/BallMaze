#pragma once

#include <memory>

#include "../subsystem_interface.h"
#include "input_axis.h"
#include "input_button.h"

class InputSubSystem : public ISubSystem
{
public:
	std::unique_ptr<InputAxis> createAxis();
	std::unique_ptr<InputButton> createButton();
	virtual float getAxisValue(const InputAxis* axis) const = 0;
	virtual bool isPressed(const InputButton* button) const = 0;
};