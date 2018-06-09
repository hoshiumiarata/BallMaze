#pragma once

#include "../window_manager_subsystem.h"

#include <GLFW/glfw3.h>

class GLFWWindowManagerSubSystem : public WindowManagerSubSystem
{
public:
	GLFWWindowManagerSubSystem(unsigned int width, unsigned int height, bool fullscreen = false, bool vsync = true);

	virtual bool init() override;
	virtual bool update(float dt) override;
	virtual bool postUpdate() override;
	virtual bool destroy() override;

	GLFWwindow* getWindow() const;

	virtual const std::string getName() const override;

private:
	unsigned int width;
	unsigned int height;
	bool fullscreen;
	bool vsync;

	GLFWwindow* window = nullptr;
};