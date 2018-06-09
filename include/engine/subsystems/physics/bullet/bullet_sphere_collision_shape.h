#pragma once

#include "bullet_collision_shape.h"

class BulletSphereCollisionShape : public BulletCollisionShape
{
public:
	explicit BulletSphereCollisionShape(float radius);
};