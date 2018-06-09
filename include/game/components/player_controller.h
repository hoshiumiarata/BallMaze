#pragma once

#include <memory>

#include "engine/components/component.h"
#include "engine/subsystems/input/input_axis.h"

class PhysicsBody;
class OrbitCamera;

class PlayerController : public Component
{
public:
	PlayerController(OrbitCamera* orbitCamera, float speed = 10.0f);
	virtual void initialize() override;
	virtual void tick(float dt) override;
private:
	const float speed;

	std::unique_ptr<InputAxis> forwardAxis;
	std::unique_ptr<InputAxis> rightAxis;

	OrbitCamera* orbitCamera;
	PhysicsBody* body = nullptr;
};