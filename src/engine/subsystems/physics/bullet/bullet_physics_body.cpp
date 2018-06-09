#include "engine/subsystems/physics/bullet/bullet_physics_body.h"
#include "engine/subsystems/physics/bullet/bullet_physics_world.h"
#include "engine/subsystems/physics/bullet/bullet_collision_shape.h"

BulletPhysicsBody::BulletPhysicsBody(BulletPhysicsWorld* world, const std::shared_ptr<BulletCollisionShape>& shape, const vec3& position, const Quaternion& rotation, float mass)
	: world(world), 
	  shape(shape), 
	  motionState(std::make_unique<btDefaultMotionState>(
		btTransform(
			btQuaternion(rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW()),
			btVector3(position.getX(), position.getY(), position.getZ()))))
{
	btVector3 inertia(0, 0, 0);
	if (mass != 0.0f)
		shape->getCollisionShape()->calculateLocalInertia(mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState.get(), shape->getCollisionShape(), inertia);
	rigidBody = std::make_unique<btRigidBody>(rigidBodyCI);
	rigidBody->setUserPointer(this);
	rigidBody->setActivationState(DISABLE_DEACTIVATION);
	world->getDynamicsWorld()->addRigidBody(rigidBody.get());
}

BulletPhysicsBody::~BulletPhysicsBody()
{
	world->getDynamicsWorld()->removeRigidBody(rigidBody.get());
}

Transform BulletPhysicsBody::getWorldTransform() const
{
	btTransform transform;
	motionState->getWorldTransform(transform);
	auto origin = transform.getOrigin();
	auto rotation = transform.getRotation();
	return Transform({ origin.getX(), origin.getY(), origin.getZ() }, Quaternion(rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW()));
}

void BulletPhysicsBody::setWorldTransform(const Transform& transform)
{
	btTransform bulletTransform(
		btQuaternion(transform.rotation.getX(), transform.rotation.getY(), transform.rotation.getZ(), transform.rotation.getW()),
		btVector3(transform.position.getX(), transform.position.getY(), transform.position.getZ()));

	rigidBody->setWorldTransform(bulletTransform);
	motionState->setWorldTransform(bulletTransform);
}

void BulletPhysicsBody::setPosition(const vec3& position)
{
	auto& transform = rigidBody->getWorldTransform();
	transform.setOrigin(btVector3(position.getX(), position.getY(), position.getZ()));
	rigidBody->setWorldTransform(transform);
	motionState->setWorldTransform(transform);
}

void BulletPhysicsBody::setRotation(const Quaternion& rotation)
{
	auto& transform = rigidBody->getWorldTransform();
	transform.setRotation(btQuaternion(rotation.getX(), rotation.getY(), rotation.getZ(), rotation.getW()));
	rigidBody->setWorldTransform(transform);
	motionState->setWorldTransform(transform);
}

void BulletPhysicsBody::setFriction(float friction)
{
	rigidBody->setFriction(friction);
}

void BulletPhysicsBody::setRollingFriction(float rollingFriction)
{
	rigidBody->setRollingFriction(rollingFriction);
}

void BulletPhysicsBody::setSpinningFriction(float spinningFriction)
{
	rigidBody->setSpinningFriction(spinningFriction);
}

void BulletPhysicsBody::setRestitution(float restitution)
{
	rigidBody->setRestitution(restitution);
}

void BulletPhysicsBody::clearForces()
{
	rigidBody->clearForces();
}

void BulletPhysicsBody::applyTorque(const vec3& torque)
{
	rigidBody->applyTorque(btVector3(torque.getX(), torque.getY(), torque.getZ()));
}

void BulletPhysicsBody::applyTorqueImpulse(const vec3& torque)
{
	rigidBody->applyTorqueImpulse(btVector3(torque.getX(), torque.getY(), torque.getZ()));
}

void BulletPhysicsBody::applyCentralForce(const vec3& force)
{
	rigidBody->applyCentralForce(btVector3(force.getX(), force.getY(), force.getZ()));
}

void BulletPhysicsBody::applyCentralImpulse(const vec3& impulse)
{
	rigidBody->applyCentralImpulse(btVector3(impulse.getX(), impulse.getY(), impulse.getZ()));
}

void BulletPhysicsBody::disableContactResponse()
{
	rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
}

void BulletPhysicsBody::stop()
{
	clearForces();
	rigidBody->setLinearVelocity(btVector3(0.0f, 0.0f, 0.0f));
	rigidBody->setAngularVelocity(btVector3(0.0f, 0.0f, 0.0f));
}

void BulletPhysicsBody::setKinematic(bool kinematic)
{
	if (kinematic)
		rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
	else
		rigidBody->setCollisionFlags(rigidBody->getCollisionFlags() & ~btCollisionObject::CF_KINEMATIC_OBJECT);
}

btRigidBody* BulletPhysicsBody::getBulletRigidBody() const
{
	return rigidBody.get();
}
