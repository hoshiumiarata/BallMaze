#include "engine/subsystems/physics/bullet/bullet_constraint.h"
#include "engine/subsystems/physics/bullet/bullet_physics_world.h"

BulletConstraint::BulletConstraint(const std::shared_ptr<PhysicsBody>& bodyA, const std::shared_ptr<PhysicsBody>& bodyB, BulletPhysicsWorld* world, std::unique_ptr<btTypedConstraint> constraint)
	: Constraint(bodyA, bodyB), world(world), constraint(std::move(constraint))
{
	world->getDynamicsWorld()->addConstraint(this->constraint.get());
}

BulletConstraint::~BulletConstraint()
{
	world->getDynamicsWorld()->removeConstraint(constraint.get());
}
