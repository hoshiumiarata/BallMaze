#pragma once

#include <memory>

#include "../physics_subsystem.h"
#include <btBulletDynamicsCommon.h>

class BulletPhysicsWorld;

class BulletPhysicsSubSustem : public PhysicsSubSystem
{
public:
	virtual bool init() override;
	virtual bool update(float dt) override;
	virtual bool postUpdate() override;
	virtual bool destroy() override;

	virtual std::shared_ptr<PhysicsWorld> createPhysicsWorld() override;

	virtual std::shared_ptr<CollisionShape> createEmptyShape() override;
	virtual std::shared_ptr<CollisionShape> createSphereShape(float radius) override;
	virtual std::shared_ptr<CollisionShape> createBoxShape(const vec3& halfExtents) override;
	virtual std::shared_ptr<CollisionShape> createMeshShape(const std::shared_ptr<Mesh>& mesh, const vec3& scale) override;

	virtual const std::string getName() const override;
};