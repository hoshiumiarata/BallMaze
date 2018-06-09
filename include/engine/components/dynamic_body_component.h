#pragma once

#include <memory>

#include "component.h"

class PhysicsBody;

class DynamicBodyComponent : public Component
{
public:
	explicit DynamicBodyComponent(const std::shared_ptr<PhysicsBody>& physicsBody);

	virtual void initialize() override;
	virtual void tick(float dt) override;

	std::shared_ptr<PhysicsBody> getPhysicsBody() const;
private:
	void updateVisual();

	std::shared_ptr<PhysicsBody> physicsBody;
};

