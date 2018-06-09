#pragma once

#include <memory>

#include "../physics_body.h"

#include <btBulletDynamicsCommon.h>

class BulletPhysicsWorld;
class BulletCollisionShape;

class BulletPhysicsBody : public PhysicsBody
{
public:
	BulletPhysicsBody(BulletPhysicsWorld* world, const std::shared_ptr<BulletCollisionShape>& shape, const vec3& position, const Quaternion& rotation, float mass);
	~BulletPhysicsBody();

	virtual Transform getWorldTransform() const override;

	virtual void setWorldTransform(const Transform& transform) override;
	virtual void setPosition(const vec3& position) override;
	virtual void setRotation(const Quaternion& rotation) override;

	virtual void setFriction(float friction) override;
	virtual void setRollingFriction(float rollingFriction) override;
	virtual void setSpinningFriction(float spinningFriction) override;
	virtual void setRestitution(float restitution) override;
	virtual void clearForces() override;

	virtual void applyTorque(const vec3& torque) override;
	virtual void applyTorqueImpulse(const vec3& torque) override;
	virtual void applyCentralForce(const vec3& force) override;
	virtual void applyCentralImpulse(const vec3& impulse) override;

	virtual void disableContactResponse() override;
	virtual void stop() override;

	virtual void setKinematic(bool kinematic) override;

	btRigidBody* getBulletRigidBody() const;

private:
	BulletPhysicsWorld* world;
	std::unique_ptr<btMotionState> motionState;
	std::unique_ptr<btRigidBody> rigidBody;
	std::shared_ptr<BulletCollisionShape> shape;
};
