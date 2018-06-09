#include "engine/subsystems/physics/bullet/bullet_physics_subsystem.h"
#include "engine/subsystems/physics/bullet/bullet_sphere_collision_shape.h"
#include "engine/subsystems/physics/bullet/bullet_box_collision_shape.h"
#include "engine/subsystems/physics/bullet/bullet_mesh_collision_shape.h"
#include "engine/subsystems/physics/bullet/bullet_physics_body.h"
#include "engine/subsystems/physics/bullet/bullet_physics_world.h"

#include "engine/engine.h"

#include <iostream>

bool BulletPhysicsSubSustem::init()
{
	return true;
}

bool BulletPhysicsSubSustem::update(float dt)
{
	if (physicsWorld)
		physicsWorld->update(dt * getEngine()->getTimeScale());

	return true;
}

bool BulletPhysicsSubSustem::postUpdate()
{
	return true;
}

bool BulletPhysicsSubSustem::destroy()
{
	return true;
}

std::shared_ptr<PhysicsWorld> BulletPhysicsSubSustem::createPhysicsWorld()
{
	return std::make_shared<BulletPhysicsWorld>();
}

std::shared_ptr<CollisionShape> BulletPhysicsSubSustem::createEmptyShape()
{
	return std::make_shared<BulletCollisionShape>(std::make_unique<btEmptyShape>());
}

std::shared_ptr<CollisionShape> BulletPhysicsSubSustem::createSphereShape(float radius)
{
	return std::make_shared<BulletSphereCollisionShape>(radius);
}

std::shared_ptr<CollisionShape> BulletPhysicsSubSustem::createBoxShape(const vec3& halfExtents)
{
	return std::make_shared<BulletBoxCollisionShape>(halfExtents);
}

std::shared_ptr<CollisionShape> BulletPhysicsSubSustem::createMeshShape(const std::shared_ptr<Mesh>& mesh, const vec3& scale)
{
	return std::make_shared<BulletMeshCollisionShape>(mesh, scale);
}

const std::string BulletPhysicsSubSustem::getName() const
{
	return "Bullet Physics";
}
