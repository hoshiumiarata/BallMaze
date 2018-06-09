#pragma once

#include <memory>

#include "../subsystem_interface.h"

class Scene;

class SceneManagerSubSystem : public ISubSystem
{
public:
	SceneManagerSubSystem();

	virtual bool init() override;
	virtual bool update(float dt) override;
	virtual bool postUpdate() override;
	virtual bool destroy() override;

	virtual const std::string getName() const override;

	void setScene(const std::shared_ptr<Scene>& scene);

private:
	void sceneSetup();

	std::shared_ptr<Scene> nextScene;
	std::shared_ptr<Scene> scene;

	bool initialized = false;
};