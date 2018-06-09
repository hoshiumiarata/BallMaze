#pragma once

#include "../physics_world.h"

#include <btBulletDynamicsCommon.h>

class BulletPhysicsWorld : public PhysicsWorld
{
public:
	BulletPhysicsWorld();
	~BulletPhysicsWorld();

	virtual void update(float dt) override;

	virtual std::shared_ptr<PhysicsBody> createPhysicsBody(const std::shared_ptr<CollisionShape>& shape, const vec3& position, const Quaternion& rotation, float mass) override;
	virtual std::vector<Contact> getContacts(PhysicsBody* bodyA, PhysicsBody* bodyB) override;
	virtual HitInfo rayCast(const vec3& start, const vec3& end) const override;
	virtual std::vector<HitInfo> rayCastAll(const vec3& start, const vec3& end) const override;
	virtual std::shared_ptr<Constraint> createPointConstraint(const std::shared_ptr<PhysicsBody>& bodyA, const std::shared_ptr<PhysicsBody>& bodyB, const vec3& pivotA, const vec3& pivotB) override;

	btDiscreteDynamicsWorld* getDynamicsWorld() const;

private:
	btBroadphaseInterface* broadphase = nullptr;
	btDefaultCollisionConfiguration* collisionConfiguration = nullptr;
	btCollisionDispatcher* dispatcher = nullptr;
	btSequentialImpulseConstraintSolver* solver = nullptr;
	btDiscreteDynamicsWorld* dynamicsWorld = nullptr;
};