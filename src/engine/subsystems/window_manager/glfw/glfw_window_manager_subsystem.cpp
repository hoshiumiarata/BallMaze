#include "engine/subsystems/window_manager/glfw/glfw_window_manager_subsystem.h"

GLFWWindowManagerSubSystem::GLFWWindowManagerSubSystem(unsigned int width, unsigned int height, bool fullscreen, bool vsync)
	: width(width), height(height), fullscreen(fullscreen), vsync(vsync)
{
}

bool GLFWWindowManagerSubSystem::init()
{
	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_SAMPLES, 2);
	
	GLFWmonitor* monitor = nullptr;

	if (fullscreen)
	{
		monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		if (width == 0)
			width = mode->width;
		if (height == 0)
			height = mode->height;
	}

	window = glfwCreateWindow(width, height, "", monitor, nullptr);

	if (!window)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);

	if (vsync)
		glfwSwapInterval(1);

	glfwSetWindowUserPointer(window, this);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	setWindowWidth(width);
	setWindowHeight(height);
	
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		auto manager = reinterpret_cast<GLFWWindowManagerSubSystem*>(glfwGetWindowUserPointer(window));
		manager->setWindowWidth(width);
		manager->setWindowHeight(height);
	});

	return true;
}

bool GLFWWindowManagerSubSystem::update(float dt)
{
	return !glfwWindowShouldClose(window);
}

bool GLFWWindowManagerSubSystem::postUpdate()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
	return true;
}

bool GLFWWindowManagerSubSystem::destroy()
{
	glfwTerminate();
	return true;
}

GLFWwindow* GLFWWindowManagerSubSystem::getWindow() const
{
	return window;
}

const std::string GLFWWindowManagerSubSystem::getName() const
{
	return "GLFW Window Manager";
}
