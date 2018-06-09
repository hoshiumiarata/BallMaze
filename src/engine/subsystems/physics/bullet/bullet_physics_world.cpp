#include "engine/subsystems/physics/bullet/bullet_physics_world.h"
#include "engine/subsystems/physics/bullet/bullet_physics_body.h"
#include "engine/subsystems/physics/bullet/bullet_constraint.h"
#include "engine/subsystems/physics/bullet/bullet_collision_shape.h"
#include "engine/subsystems/physics/contact.h"
#include "engine/subsystems/physics/hit_info.h"

BulletPhysicsWorld::BulletPhysicsWorld()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0.0f, -9.81f, 0.0f));
}

BulletPhysicsWorld::~BulletPhysicsWorld()
{
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
}

void BulletPhysicsWorld::update(float dt)
{
	dynamicsWorld->stepSimulation(dt, 4);
}

std::shared_ptr<PhysicsBody> BulletPhysicsWorld::createPhysicsBody(const std::shared_ptr<CollisionShape>& shape, const vec3& position, const Quaternion& rotation, float mass)
{
	return std::make_shared<BulletPhysicsBody>(this, std::static_pointer_cast<BulletCollisionShape>(shape), position, rotation, mass);
}

std::vector<Contact> BulletPhysicsWorld::getContacts(PhysicsBody * bodyA, PhysicsBody * bodyB)
{
	std::vector<Contact> result;

	int numManifolds = dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i < numManifolds; i++)
	{
		btPersistentManifold* contactManifold = dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		auto contactBodyA = contactManifold->getBody0()->getUserPointer();
		auto contactBodyB = contactManifold->getBody1()->getUserPointer();

		if (bodyA == contactBodyA && bodyB == contactBodyB || bodyA == contactBodyB && bodyB == contactBodyA)
		{
			int numContacts = contactManifold->getNumContacts();
			result.resize(numContacts);
			for (int j = 0; j < numContacts; j++)
			{
				btManifoldPoint& pt = contactManifold->getContactPoint(j);
				result[j].distance = pt.getDistance();
			}

			break;
		}
	}

	return result;
}

HitInfo BulletPhysicsWorld::rayCast(const vec3 & start, const vec3 & end) const
{
	btVector3 bulletStart(start.getX(), start.getY(), start.getZ());
	btVector3 bulletEnd(end.getX(), end.getY(), end.getZ());
	btCollisionWorld::ClosestRayResultCallback rayCallback(bulletStart, bulletEnd);
	dynamicsWorld->rayTest(bulletStart, bulletEnd, rayCallback);
	HitInfo info;
	info.hasHit = rayCallback.hasHit();
	if (info.hasHit)
	{
		info.physicsBody = reinterpret_cast<PhysicsBody*>(rayCallback.m_collisionObject->getUserPointer());
		info.point = { rayCallback.m_hitPointWorld.getX(), rayCallback.m_hitPointWorld.getY(), rayCallback.m_hitPointWorld.getZ() };
		info.normal = { rayCallback.m_hitNormalWorld.getX(), rayCallback.m_hitNormalWorld.getY(), rayCallback.m_hitNormalWorld.getZ() };
	}
	return info;
}

std::vector<HitInfo> BulletPhysicsWorld::rayCastAll(const vec3 & start, const vec3 & end) const
{
	btVector3 bulletStart(start.getX(), start.getY(), start.getZ());
	btVector3 bulletEnd(end.getX(), end.getY(), end.getZ());
	btCollisionWorld::AllHitsRayResultCallback rayCallback(bulletStart, bulletEnd);
	dynamicsWorld->rayTest(bulletStart, bulletEnd, rayCallback);

	std::vector<HitInfo> result(rayCallback.m_collisionObjects.size());

	for (size_t i = 0; i < result.size(); i++)
	{
		result[i].hasHit = true;
		result[i].physicsBody = reinterpret_cast<PhysicsBody*>(rayCallback.m_collisionObjects[i]->getUserPointer());
		result[i].point = { rayCallback.m_hitPointWorld[i].getX(), rayCallback.m_hitPointWorld[i].getY(), rayCallback.m_hitPointWorld[i].getZ() };
		result[i].normal = { rayCallback.m_hitNormalWorld[i].getX(), rayCallback.m_hitNormalWorld[i].getY(), rayCallback.m_hitNormalWorld[i].getZ() };
	}

	return result;
}

std::shared_ptr<Constraint> BulletPhysicsWorld::createPointConstraint(const std::shared_ptr<PhysicsBody>& bodyA, const std::shared_ptr<PhysicsBody>& bodyB, const vec3& pivotA, const vec3& pivotB)
{
	auto bulletBodyA = std::dynamic_pointer_cast<BulletPhysicsBody>(bodyA);
	auto bulletBodyB = std::dynamic_pointer_cast<BulletPhysicsBody>(bodyB);
	auto bulletConstraint = std::make_unique<btPoint2PointConstraint>(*bulletBodyA->getBulletRigidBody(), *bulletBodyB->getBulletRigidBody(), btVector3(pivotA.getX(), pivotA.getY(), pivotA.getZ()), btVector3(pivotB.getX(), pivotB.getY(), pivotB.getZ()));
	return std::make_shared<BulletConstraint>(bodyA, bodyB, this, std::move(bulletConstraint));
}

btDiscreteDynamicsWorld * BulletPhysicsWorld::getDynamicsWorld() const
{
	return dynamicsWorld;
}
