#include "engine/subsystems/physics/bullet/bullet_mesh_collision_shape.h"

BulletMeshCollisionShape::BulletMeshCollisionShape(const std::shared_ptr<Mesh>& mesh, const vec3& scale)
{
	auto& indices = mesh->getIndices();
	auto& vertices = mesh->getVertices();
	for (unsigned int i = 0; i < indices.size(); i += 3)
	{
		unsigned int index0 = indices[i];
		unsigned int index1 = indices[i + 1];
		unsigned int index2 = indices[i + 2];
		triangleMesh.addTriangle(
			btVector3(vertices[index0].getX(), vertices[index0].getY(), vertices[index0].getZ()),
			btVector3(vertices[index1].getX(), vertices[index1].getY(), vertices[index1].getZ()),
			btVector3(vertices[index2].getX(), vertices[index2].getY(), vertices[index2].getZ()));
	}
	triangleMesh.setScaling(btVector3(scale.getX(), scale.getY(), scale.getZ()));
	shape = std::make_unique<btBvhTriangleMeshShape>(&triangleMesh, true);
}
