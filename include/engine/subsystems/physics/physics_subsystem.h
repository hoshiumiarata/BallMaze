#pragma once

#include <memory>

#include "../subsystem_interface.h"

#include "engine/math/vector.h"

class PhysicsWorld;
class CollisionShape;
class Mesh;

class PhysicsSubSystem : public ISubSystem
{
public:
	virtual std::shared_ptr<PhysicsWorld> createPhysicsWorld() = 0;
	virtual std::shared_ptr<CollisionShape> createEmptyShape() = 0;
	virtual std::shared_ptr<CollisionShape> createSphereShape(float radius) = 0;
	virtual std::shared_ptr<CollisionShape> createBoxShape(const vec3& halfExtents) = 0;
	virtual std::shared_ptr<CollisionShape> createMeshShape(const std::shared_ptr<Mesh>& mesh, const vec3& scale) = 0;

	void setPhysicsWorld(const std::shared_ptr<PhysicsWorld>& physicsWorld);
	PhysicsWorld* getPhysicsWorld() const;

protected:
	std::shared_ptr<PhysicsWorld> physicsWorld;
};