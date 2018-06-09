#include "engine/subsystems/input/glfw/glfw_input_subsystem.h"
#include "engine/engine.h"
#include "engine/subsystems/window_manager/glfw/glfw_window_manager_subsystem.h"

#include <algorithm>

bool GLFWInputSubSystem::init()
{
	auto windowManager = dynamic_cast<GLFWWindowManagerSubSystem*>(getEngine()->getWindowManager());
	if (!windowManager)
		return false;

	window = windowManager->getWindow();

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwGetCursorPos(window, &lastMouseX, &lastMouseY);

	return true;
}

bool GLFWInputSubSystem::update(float dt)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	mouseDX = x - lastMouseX;
	mouseDY = y - lastMouseY;
	lastMouseX = x;
	lastMouseY = y;
	return true;
}

bool GLFWInputSubSystem::postUpdate()
{
	return true;
}

bool GLFWInputSubSystem::destroy()
{
	return true;
}

float GLFWInputSubSystem::getAxisValue(const InputAxis* axis) const
{
	for (const auto& key : axis->getKeyboardKeys())
	{
		if (glfwGetKey(window, getGLFWKey(key.key)) == GLFW_PRESS)
			return key.value;
	}

	for (const auto& gamepadAxis : axis->getGamepadAxes())
	{
		int axisCount;
		const float* axes = glfwGetJoystickAxes(gamepadAxis.gamepadIndex, &axisCount);
		int axisIndex = getGamepadAxisIndex(gamepadAxis.axis);
		if (axisIndex >= 0 && axisIndex < axisCount && std::fabs(axes[axisIndex]) > 1e-5)
			return axes[axisIndex] * gamepadAxis.value;
	}

	for (const auto& mouseAxis : axis->getMouseAxes())
	{
		double value = getMouseDelta(mouseAxis.axis);
		if (std::fabs(value) > 0.0)
			return static_cast<float>(value * mouseAxis.value);
	}

	return 0.0f;
}

bool GLFWInputSubSystem::isPressed(const InputButton* button) const
{
	const auto& keyboardKeys = button->getKeyboardKeys();
	return std::any_of(keyboardKeys.cbegin(), keyboardKeys.cend(), [this](const auto& key) -> bool {
		return glfwGetKey(window, getGLFWKey(key)) == GLFW_PRESS;
	});
}

const std::string GLFWInputSubSystem::getName() const
{
	return "GLFW Input SubSystem";
}

int GLFWInputSubSystem::getGLFWKey(Keyboard::Key key) const
{
	switch (key)
	{
	case Keyboard::Key::_0: return GLFW_KEY_0;
	case Keyboard::Key::_1: return GLFW_KEY_1;
	case Keyboard::Key::_2: return GLFW_KEY_2;
	case Keyboard::Key::_3: return GLFW_KEY_3;
	case Keyboard::Key::_4: return GLFW_KEY_4;
	case Keyboard::Key::_5: return GLFW_KEY_5;
	case Keyboard::Key::_6: return GLFW_KEY_6;
	case Keyboard::Key::_7: return GLFW_KEY_7;
	case Keyboard::Key::_8: return GLFW_KEY_8;
	case Keyboard::Key::_9: return GLFW_KEY_9;
	case Keyboard::Key::A: return GLFW_KEY_A;
	case Keyboard::Key::B: return GLFW_KEY_B;
	case Keyboard::Key::C: return GLFW_KEY_C;
	case Keyboard::Key::D: return GLFW_KEY_D;
	case Keyboard::Key::E: return GLFW_KEY_E;
	case Keyboard::Key::F: return GLFW_KEY_F;
	case Keyboard::Key::G: return GLFW_KEY_G;
	case Keyboard::Key::H: return GLFW_KEY_H;
	case Keyboard::Key::I: return GLFW_KEY_I;
	case Keyboard::Key::J: return GLFW_KEY_J;
	case Keyboard::Key::K: return GLFW_KEY_K;
	case Keyboard::Key::L: return GLFW_KEY_L;
	case Keyboard::Key::M: return GLFW_KEY_M;
	case Keyboard::Key::N: return GLFW_KEY_N;
	case Keyboard::Key::O: return GLFW_KEY_O;
	case Keyboard::Key::P: return GLFW_KEY_P;
	case Keyboard::Key::Q: return GLFW_KEY_Q;
	case Keyboard::Key::R: return GLFW_KEY_R;
	case Keyboard::Key::S: return GLFW_KEY_S;
	case Keyboard::Key::T: return GLFW_KEY_T;
	case Keyboard::Key::U: return GLFW_KEY_U;
	case Keyboard::Key::V: return GLFW_KEY_V;
	case Keyboard::Key::W: return GLFW_KEY_W;
	case Keyboard::Key::X: return GLFW_KEY_X;
	case Keyboard::Key::Y: return GLFW_KEY_Y;
	case Keyboard::Key::Z: return GLFW_KEY_Z;
	case Keyboard::Key::Escape: return GLFW_KEY_ESCAPE;
	case Keyboard::Key::Enter: return GLFW_KEY_ENTER;
	case Keyboard::Key::Tab: return GLFW_KEY_TAB;
	case Keyboard::Key::Up: return GLFW_KEY_UP;
	case Keyboard::Key::Down: return GLFW_KEY_DOWN;
	case Keyboard::Key::Left: return GLFW_KEY_LEFT;
	case Keyboard::Key::Right: return GLFW_KEY_RIGHT;
	}
	return -1;
}

int GLFWInputSubSystem::getGamepadAxisIndex(Gamepad::Axis axis) const
{
	switch (axis)
	{
	case Gamepad::Axis::LeftStickX: return 0;
	case Gamepad::Axis::LeftStickY: return 1;
	case Gamepad::Axis::RightStickX: return 2;
	case Gamepad::Axis::RightStickY: return 3;
	}
	return -1;
}

double GLFWInputSubSystem::getMouseDelta(Mouse::Axis axis) const
{
	switch (axis)
	{
	case Mouse::Axis::X: return mouseDX;
	case Mouse::Axis::Y: return mouseDY;
	}
	return 0.0;
}
