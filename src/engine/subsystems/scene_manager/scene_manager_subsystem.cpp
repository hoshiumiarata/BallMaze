#include "engine/subsystems/scene_manager/scene_manager_subsystem.h"
#include "engine/scene.h"

SceneManagerSubSystem::SceneManagerSubSystem() = default;

bool SceneManagerSubSystem::init()
{
	initialized = true;
	if (scene)
		sceneSetup();

	return true;
}

bool SceneManagerSubSystem::update(float dt)
{
	if (nextScene)
	{
		scene = std::move(nextScene);
		sceneSetup();
	}

	if (scene)
		scene->tick(dt);
	return true;
}

bool SceneManagerSubSystem::postUpdate()
{
	return true;
}

bool SceneManagerSubSystem::destroy()
{
	if (scene)
		scene->end();

	scene.reset();
	initialized = false;

	return true;
}

const std::string SceneManagerSubSystem::getName() const
{
	return "Scene Manager";
}

void SceneManagerSubSystem::setScene(const std::shared_ptr<Scene>& scene)
{
	if (initialized)
		nextScene = scene;
	else
		this->scene = scene;
}

void SceneManagerSubSystem::sceneSetup()
{
	scene->setEngine(getEngine());
	scene->start();
}
