#pragma once

#include <memory>

#include "component.h"

class Camera;

class CameraComponent : public Component
{
public:
	explicit CameraComponent(const std::shared_ptr<Camera>& camera);

	std::shared_ptr<Camera> getCamera() const;

	virtual void initialize() override;
	virtual void tick(float dt) override;

	void updateCamera();
private:
	std::shared_ptr<Camera> camera;
};