#include "engine/components/trigger_component.h"
#include "engine/engine.h"
#include "engine/subsystems/physics/physics_subsystem.h"
#include "engine/subsystems/physics/physics_world.h"
#include "engine/subsystems/physics/contact.h"

#include <algorithm>

TriggerComponent::TriggerComponent(const std::shared_ptr<PhysicsBody>& physicsBody)
	: physicsBody(physicsBody)
{

}

void TriggerComponent::initialize()
{

}

void TriggerComponent::tick(float dt)
{
	for (auto& trigger : triggers)
	{
		auto contacts = getEngine()->getPhysics()->getPhysicsWorld()->getContacts(physicsBody.get(), trigger.body);
		auto contactsCount = std::count_if(contacts.begin(), contacts.end(), [&trigger](auto& contact) {
			return contact.distance <= trigger.distance;
		});
		if (contactsCount > 0 && !trigger.activated)
		{
			trigger.activated = true;
			trigger.activatedCallback();
		}
		else if (contactsCount == 0 && trigger.activated)
		{
			trigger.activated = false;
			if (trigger.deactivatedCallback)
				trigger.deactivatedCallback();
		}
	}
}

void TriggerComponent::addTrigger(PhysicsBody* body, const std::function<void()>& activatedCallback, const std::function<void()>& deactivatedCallback, float distance)
{
	triggers.emplace_back(false, body, activatedCallback, deactivatedCallback, distance);
}

void TriggerComponent::addTrigger(PhysicsBody* body, const std::function<void()>& activatedCallback, float distance)
{
	addTrigger(body, activatedCallback, std::function<void()>(), distance);
}

std::shared_ptr<PhysicsBody> TriggerComponent::getPhysicsBody() const
{
	return physicsBody;
}

TriggerComponent::TriggerState::TriggerState(bool activated, PhysicsBody* body, const std::function<void()>& activatedCallback, const std::function<void()>& deactivatedCallback, float distance)
	: activated(activated), body(body), activatedCallback(activatedCallback), deactivatedCallback(deactivatedCallback), distance(distance)
{

}
