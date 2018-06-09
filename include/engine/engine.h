#pragma once

#include <chrono>
#include <memory>
#include <vector>

#include "camera.h"
#include "timer.h"

class ISubSystem;
class PhysicsSubSystem;
class FileManagerSubSystem;
class WindowManagerSubSystem;
class InputSubSystem;
class SceneManagerSubSystem;
class GraphicsSubSystem;

class Engine
{
public:
	~Engine();

	void start();
	void stop();

	void addSubSystem(ISubSystem* subsystem);
	void addSubSystem(PhysicsSubSystem* physics);
	void addSubSystem(FileManagerSubSystem* fileManager);
	void addSubSystem(WindowManagerSubSystem* windowManager);
	void addSubSystem(InputSubSystem* input);
	void addSubSystem(SceneManagerSubSystem* sceneManager);
	void addSubSystem(GraphicsSubSystem* graphics);

	PhysicsSubSystem* getPhysics() const;
	FileManagerSubSystem* getFileManager() const;
	WindowManagerSubSystem* getWindowManager() const;
	InputSubSystem* getInput() const;
	SceneManagerSubSystem* getSceneManager() const;
	GraphicsSubSystem* getGraphics() const;

	std::shared_ptr<Camera> getCamera() const;
	void setCamera(const std::shared_ptr<Camera>& camera);

	float getTimeScale() const;
	void setTimeScale(float timeScale);

	void timerStart(const std::shared_ptr<Timer>& timer);
	void timerStop(const std::shared_ptr<Timer>& timer);
private:
	void loop();
	void end();
	void processTimers();
	bool processSubsystems();

	const float fpsLimit = 60.0f;
	const float timerDeltaTimeLimit = 1e-4f;

	float timeScale = 1.0f;

	bool stopped = false;

	std::shared_ptr<Camera> camera;

	std::vector<std::unique_ptr<ISubSystem>> subsystems;
	FileManagerSubSystem* fileManager = nullptr;
	PhysicsSubSystem* physics = nullptr;
	WindowManagerSubSystem* windowManager = nullptr;
	InputSubSystem* input = nullptr;
	SceneManagerSubSystem* sceneManager = nullptr;
	GraphicsSubSystem* graphics = nullptr;

	std::vector<std::pair<std::shared_ptr<Timer>, std::chrono::high_resolution_clock::time_point>> timers;
	std::vector<std::shared_ptr<Timer>> timersToStop;

	std::chrono::high_resolution_clock::time_point lastTime;
};