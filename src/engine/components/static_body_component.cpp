#include "engine/components/static_body_component.h"
#include "engine/subsystems/physics/physics_body.h"

StaticBodyComponent::StaticBodyComponent(const std::shared_ptr<PhysicsBody>& physicsBody)
	: physicsBody(physicsBody)
{

}

StaticBodyComponent::~StaticBodyComponent() = default;

void StaticBodyComponent::initialize()
{

}

void StaticBodyComponent::tick(float dt)
{

}
