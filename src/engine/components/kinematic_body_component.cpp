#include "engine/components/kinematic_body_component.h"
#include "engine/subsystems/physics/physics_body.h"

void KinematicBodyComponent::initialize()
{
	DynamicBodyComponent::initialize();
	getPhysicsBody()->setKinematic(true);
}
