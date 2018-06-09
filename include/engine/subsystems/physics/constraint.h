#pragma once

#include <memory>

class PhysicsBody;

class Constraint
{
public:
	Constraint(const std::shared_ptr<PhysicsBody>& bodyA, const std::shared_ptr<PhysicsBody>& bodyB);

private:
	std::shared_ptr<PhysicsBody> bodyA;
	std::shared_ptr<PhysicsBody> bodyB;
};