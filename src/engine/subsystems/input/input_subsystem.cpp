#include "engine/subsystems/input/input_subsystem.h"

std::unique_ptr<InputAxis> InputSubSystem::createAxis()
{
	return std::make_unique<InputAxis>(this);
}

std::unique_ptr<InputButton> InputSubSystem::createButton()
{
	return std::make_unique<InputButton>(this);
}
