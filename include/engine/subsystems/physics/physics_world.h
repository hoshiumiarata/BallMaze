#pragma once

#include <vector>
#include <memory>

#include "engine/math/vector.h"
#include "engine/math/quaternion.h"

class PhysicsBody;
class CollisionShape;
class Constraint;
struct Contact;
struct HitInfo;

class PhysicsWorld
{
public:
	virtual ~PhysicsWorld() {};
	virtual void update(float dt) = 0;

	virtual std::shared_ptr<PhysicsBody> createPhysicsBody(const std::shared_ptr<CollisionShape>& shape, const vec3& position, const Quaternion& rotation, float mass) = 0;
	virtual std::vector<Contact> getContacts(PhysicsBody* bodyA, PhysicsBody* bodyB) = 0;
	virtual HitInfo rayCast(const vec3& start, const vec3& end) const = 0;
	virtual std::vector<HitInfo> rayCastAll(const vec3& start, const vec3& end) const = 0;

	virtual std::shared_ptr<Constraint> createPointConstraint(const std::shared_ptr<PhysicsBody>& bodyA, const std::shared_ptr<PhysicsBody>& bodyB, const vec3& pivotA, const vec3& pivotB) = 0;
};