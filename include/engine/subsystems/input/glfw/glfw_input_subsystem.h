#pragma once

#include "../input_subsystem.h"
#include "../keyboard.h"
#include "../gamepad.h"

#include <GLFW/glfw3.h>

class GLFWInputSubSystem : public InputSubSystem
{
public:

	virtual bool init() override;
	virtual bool update(float dt) override;
	virtual bool postUpdate() override;
	virtual bool destroy() override;

	virtual float getAxisValue(const InputAxis* axis) const override;
	virtual bool isPressed(const InputButton* button) const override;

	virtual const std::string getName() const override;
private:
	int getGLFWKey(Keyboard::Key key) const;
	int getGamepadAxisIndex(Gamepad::Axis axis) const;
	double getMouseDelta(Mouse::Axis axis) const;

	GLFWwindow* window = nullptr;
	double lastMouseX = 0.0, lastMouseY = 0.0;
	double mouseDX = 0.0, mouseDY = 0.0;
};