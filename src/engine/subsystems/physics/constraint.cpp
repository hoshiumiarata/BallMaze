#include "engine/subsystems/physics/constraint.h"
#include "engine/subsystems/physics/physics_body.h"

Constraint::Constraint(const std::shared_ptr<PhysicsBody>& bodyA, const std::shared_ptr<PhysicsBody>& bodyB)
	: bodyA(bodyA), bodyB(bodyB)
{
}
