#pragma once

#include "../subsystem_interface.h"

class WindowManagerSubSystem : public ISubSystem
{
public:
	unsigned int getWindowWidth() const;
	unsigned int getWindowHeight() const;
	float getAspectRatio() const;
protected:
	void setWindowWidth(unsigned int width);
	void setWindowHeight(unsigned int height);
private:
	unsigned int windowWidth = 0;
	unsigned int windowHeight = 0;
};
