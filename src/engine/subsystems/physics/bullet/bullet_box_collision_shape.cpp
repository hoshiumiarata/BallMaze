#include "engine/subsystems/physics/bullet/bullet_box_collision_shape.h"

BulletBoxCollisionShape::BulletBoxCollisionShape(const vec3& halfExtents)
	: BulletCollisionShape(std::make_unique<btBoxShape>(btVector3(halfExtents.getX(), halfExtents.getY(), halfExtents.getZ())))
{

}
