#include "engine/subsystems/physics/bullet/bullet_collision_shape.h"

BulletCollisionShape::BulletCollisionShape() = default;

BulletCollisionShape::BulletCollisionShape(std::unique_ptr<btCollisionShape> shape)
	: shape(std::move(shape))
{

}

btCollisionShape* BulletCollisionShape::getCollisionShape() const
{
	return shape.get();
}
