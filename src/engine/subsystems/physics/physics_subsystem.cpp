#include "engine/subsystems/physics/physics_subsystem.h"

void PhysicsSubSystem::setPhysicsWorld(const std::shared_ptr<PhysicsWorld>& physicsWorld)
{
	this->physicsWorld = physicsWorld;
}

PhysicsWorld* PhysicsSubSystem::getPhysicsWorld() const
{
	return physicsWorld.get();
}
