#include "engine/components/physics_world_component.h"
#include "engine/engine.h"
#include "engine/subsystems/physics/physics_subsystem.h"

void PhysicsWorldComponent::initialize()
{
	physicsWorld = getEngine()->getPhysics()->createPhysicsWorld();
}

void PhysicsWorldComponent::tick(float dt)
{
	if (getEngine()->getPhysics()->getPhysicsWorld() != physicsWorld.get())
		getEngine()->getPhysics()->setPhysicsWorld(physicsWorld);
}

PhysicsWorld* PhysicsWorldComponent::getPhysicsWorld() const
{
	return physicsWorld.get();
}
