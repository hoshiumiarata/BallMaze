#pragma once

#include <memory>

#include "../constraint.h"

#include <btBulletDynamicsCommon.h>

class BulletPhysicsWorld;
class PhysicsBody;

class BulletConstraint : public Constraint
{
public:
	BulletConstraint(const std::shared_ptr<PhysicsBody>& bodyA, const std::shared_ptr<PhysicsBody>& bodyB, BulletPhysicsWorld* world, std::unique_ptr<btTypedConstraint> constraint);
	~BulletConstraint();

private:
	BulletPhysicsWorld* world;
	std::unique_ptr<btTypedConstraint> constraint;
};