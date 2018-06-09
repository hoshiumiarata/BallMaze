#pragma once

#include <memory>

#include "component.h"

class PhysicsBody;

class StaticBodyComponent : public Component
{
public:
	explicit StaticBodyComponent(const std::shared_ptr<PhysicsBody>& physicsBody);
	~StaticBodyComponent();

	virtual void initialize() override;
	virtual void tick(float dt) override;

private:
	std::shared_ptr<PhysicsBody> physicsBody;
};