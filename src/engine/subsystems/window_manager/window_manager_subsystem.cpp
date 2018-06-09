#include "engine/subsystems/window_manager/window_manager_subsystem.h"

unsigned int WindowManagerSubSystem::getWindowWidth() const
{
	return windowWidth;
}

unsigned int WindowManagerSubSystem::getWindowHeight() const
{
	return windowHeight;
}

float WindowManagerSubSystem::getAspectRatio() const
{
	return static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
}

void WindowManagerSubSystem::setWindowWidth(unsigned int width)
{
	windowWidth = width;
}

void WindowManagerSubSystem::setWindowHeight(unsigned int height)
{
	windowHeight = height;
}
