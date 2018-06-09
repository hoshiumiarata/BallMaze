#pragma once

#include <memory>
#include "../collision_shape.h"

#include <btBulletDynamicsCommon.h>

class BulletCollisionShape : public CollisionShape
{
public:
	BulletCollisionShape();
	explicit BulletCollisionShape(std::unique_ptr<btCollisionShape> shape);

	btCollisionShape* getCollisionShape() const;
protected:
	std::unique_ptr<btCollisionShape> shape;
};