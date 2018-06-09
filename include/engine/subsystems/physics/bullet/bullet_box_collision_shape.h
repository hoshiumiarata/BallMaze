#pragma once

#include "bullet_collision_shape.h"
#include "engine/math/vector.h"

class BulletBoxCollisionShape : public BulletCollisionShape
{
public:
	explicit BulletBoxCollisionShape(const vec3& halfExtents);
};