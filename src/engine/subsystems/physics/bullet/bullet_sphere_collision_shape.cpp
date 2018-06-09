#include "engine/subsystems/physics/bullet/bullet_sphere_collision_shape.h"

BulletSphereCollisionShape::BulletSphereCollisionShape(float radius)
	: BulletCollisionShape(std::make_unique<btSphereShape>(radius))
{

}
