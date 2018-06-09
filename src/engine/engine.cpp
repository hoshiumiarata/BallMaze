#include "engine/engine.h"

#include "engine/subsystems/physics/physics_subsystem.h"
#include "engine/subsystems/file_manager/file_manager_subsystem.h"
#include "engine/subsystems/window_manager/window_manager_subsystem.h"
#include "engine/subsystems/input/input_subsystem.h"
#include "engine/subsystems/scene_manager/scene_manager_subsystem.h"
#include "engine/subsystems/graphics/graphics_subsystem.h"

#include <algorithm>
#include <exception>

Engine::~Engine() = default;

void Engine::start()
{
	for (const auto& subsystem : subsystems)
	{
		const bool initialized = subsystem->init();
		if (!initialized)
			throw std::runtime_error(subsystem->getName() + ": initialization error");
	}

	lastTime = std::chrono::high_resolution_clock::now();

	try
	{
		loop();
	}
	catch (...)
	{
		end();
		throw;
	}
	end();
}

void Engine::stop()
{
	stopped = true;
}

void Engine::addSubSystem(ISubSystem* subsystem)
{
	subsystem->setEngine(this);
	subsystems.push_back(std::unique_ptr<ISubSystem>(subsystem));
}

void Engine::addSubSystem(PhysicsSubSystem* physics)
{
	this->physics = physics;
	addSubSystem(static_cast<ISubSystem*>(physics));
}

void Engine::addSubSystem(FileManagerSubSystem* fileManager)
{
	this->fileManager = fileManager;
	addSubSystem(static_cast<ISubSystem*>(fileManager));
}

void Engine::addSubSystem(WindowManagerSubSystem* windowManager)
{
	this->windowManager = windowManager;
	addSubSystem(static_cast<ISubSystem*>(windowManager));
}

void Engine::addSubSystem(InputSubSystem* input)
{
	this->input = input;
	addSubSystem(static_cast<ISubSystem*>(input));
}

void Engine::addSubSystem(SceneManagerSubSystem* sceneManager)
{
	this->sceneManager = sceneManager;
	addSubSystem(static_cast<ISubSystem*>(sceneManager));
}

void Engine::addSubSystem(GraphicsSubSystem* graphics)
{
	this->graphics = graphics;
	addSubSystem(static_cast<ISubSystem*>(graphics));
}

PhysicsSubSystem* Engine::getPhysics() const
{
	return physics;
}

FileManagerSubSystem* Engine::getFileManager() const
{
	return fileManager;
}

WindowManagerSubSystem* Engine::getWindowManager() const
{
	return windowManager;
}

InputSubSystem* Engine::getInput() const
{
	return input;
}

SceneManagerSubSystem* Engine::getSceneManager() const
{
	return sceneManager;
}

GraphicsSubSystem* Engine::getGraphics() const
{
	return graphics;
}

std::shared_ptr<Camera> Engine::getCamera() const
{
	return camera;
}

void Engine::setCamera(const std::shared_ptr<Camera>& camera)
{
	this->camera = camera;
}

float Engine::getTimeScale() const
{
	return timeScale;
}

void Engine::setTimeScale(float timeScale)
{
	this->timeScale = timeScale;
}

void Engine::loop()
{
	while (!stopped)
	{
		processTimers();

		if (!processSubsystems())
			break;
	}
}

void Engine::end()
{
	timers.clear();

	for (auto it = subsystems.rbegin(); it != subsystems.rend(); it++)
	{
		const auto& subsystem = it->get();

		const bool destroyed = subsystem->destroy();
		if (!destroyed)
			throw std::runtime_error(subsystem->getName() + ": destroying error");
	}
}

void Engine::processTimers()
{
	if (!timers.empty())
	{
		for (auto& timer : timersToStop)
		{
			auto it = std::find_if(timers.begin(), timers.end(), [&timer](auto& t) -> bool { return t.first == timer; });
			if (it != timers.end())
				timers.erase(it);
		}

		timersToStop.clear();

		for (size_t i = 0; i < timers.size();)
		{
			const auto time = std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> timerDt = time - timers[i].second;
			if (timerDt.count() < timerDeltaTimeLimit)
				continue;
			auto isLastTime = timers[i].first->step(timerDt.count(), timeScale);
			timers[i].second = time;
			if (isLastTime)
				timers.erase(timers.begin() + i);
			else
				i++;
		}
	}
}

bool Engine::processSubsystems()
{
	const auto time = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> dt = time - lastTime;

	const float frameTime = 1.0f / fpsLimit;
	if (dt.count() >= frameTime)
	{
		for (const auto& subsystem : subsystems)
		{
			const bool updated = subsystem->update(dt.count());
			if (!updated)
				return false;
		}

		for (auto it = subsystems.rbegin(); it != subsystems.rend(); it++)
		{
			const auto& subsystem = it->get();

			const bool updated = subsystem->postUpdate();
			if (!updated)
				return false;
		}

		lastTime = time;
	}

	return true;
}

void Engine::timerStart(const std::shared_ptr<Timer>& timer)
{
	timers.emplace_back(timer, std::chrono::high_resolution_clock::now());
}

void Engine::timerStop(const std::shared_ptr<Timer>& timer)
{
	timersToStop.push_back(timer);
}