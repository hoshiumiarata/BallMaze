#pragma once

#include <memory>

#include "component.h"

class PhysicsWorld;

class PhysicsWorldComponent : public Component
{
public:
	virtual void initialize() override;
	virtual void tick(float dt) override;

	PhysicsWorld* getPhysicsWorld() const;

private:
	std::shared_ptr<PhysicsWorld> physicsWorld;
};