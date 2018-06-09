#pragma once

#include <memory>
#include <functional>
#include <vector>

#include "component.h"

class PhysicsBody;

class TriggerComponent : public Component
{
public:
	explicit TriggerComponent(const std::shared_ptr<PhysicsBody>& physicsBody);

	virtual void initialize() override;

	struct TriggerState
	{
		TriggerState(bool activated, PhysicsBody* body, const std::function<void()>& activatedCallback, const std::function<void()>& deactivatedCallback, float distance);

		bool activated;
		PhysicsBody* body;
		std::function<void()> activatedCallback;
		std::function<void()> deactivatedCallback;
		float distance;
	};

	virtual void tick(float dt) override;

	void addTrigger(PhysicsBody* body, const std::function<void()>& activatedCallback, const std::function<void()>& deactivatedCallback, float distance = 0.0f);
	void addTrigger(PhysicsBody* body, const std::function<void()>& activatedCallback, float distance = 0.0f);

	std::shared_ptr<PhysicsBody> getPhysicsBody() const;
private:
	std::shared_ptr<PhysicsBody> physicsBody;
	std::vector<TriggerState> triggers;
};