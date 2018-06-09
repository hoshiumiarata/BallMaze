#include "engine/components/dynamic_body_component.h"
#include "engine/node.h"
#include "engine/subsystems/physics/physics_body.h"

DynamicBodyComponent::DynamicBodyComponent(const std::shared_ptr<PhysicsBody>& physicsBody)
	: physicsBody(physicsBody)
{

}

void DynamicBodyComponent::initialize()
{
	updateVisual();
}

void DynamicBodyComponent::tick(float dt)
{
	updateVisual();
}

std::shared_ptr<PhysicsBody> DynamicBodyComponent::getPhysicsBody() const
{
	return physicsBody;
}

void DynamicBodyComponent::updateVisual()
{
	getParent()->updateWorldTransform([&](auto& transform) {
		Transform physicsWorldTransform = physicsBody->getWorldTransform();
		transform.position = physicsWorldTransform.position;
		transform.rotation = physicsWorldTransform.rotation;
	});
}
