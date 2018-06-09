#pragma once

#include "bullet_collision_shape.h"
#include "../../../mesh.h"

class BulletMeshCollisionShape : public BulletCollisionShape
{
public:
	BulletMeshCollisionShape(const std::shared_ptr<Mesh>& mesh, const vec3& scale);
private:
	btTriangleMesh triangleMesh;
};