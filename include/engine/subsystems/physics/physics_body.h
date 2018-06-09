#pragma once

#include "engine/math/transform.h"
#include "engine/math/vector.h"

class PhysicsBody
{
public:
	virtual ~PhysicsBody() = default;

	virtual Transform getWorldTransform() const = 0;

	virtual void setWorldTransform(const Transform& transform) = 0;
	virtual void setPosition(const vec3& position) = 0;
	virtual void setRotation(const Quaternion& rotation) = 0;

	virtual void setFriction(float friction) = 0;
	virtual void setRollingFriction(float rollingFriction) = 0;
	virtual void setSpinningFriction(float spinningFriction) = 0;
	virtual void setRestitution(float restitution) = 0;

	virtual void clearForces() = 0;
	virtual void applyTorque(const vec3& torque) = 0;
	virtual void applyTorqueImpulse(const vec3& torque) = 0;
	virtual void applyCentralForce(const vec3& force) = 0;
	virtual void applyCentralImpulse(const vec3& impulse) = 0;

	virtual void stop() = 0;
	virtual void disableContactResponse() = 0;

	virtual void setKinematic(bool kinematic) = 0;
};