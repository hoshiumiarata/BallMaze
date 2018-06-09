#include "engine/components/mesh_component.h"
#include "engine/engine.h"
#include "engine/node.h"
#include "engine/subsystems/graphics/graphics_subsystem.h"
#include "engine/subsystems/graphics/mesh_renderer.h"

MeshComponent::MeshComponent(const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material)
	: mesh(mesh), material(material)
{

}

std::shared_ptr<Mesh> MeshComponent::getMesh() const
{
	return mesh;
}

std::shared_ptr<Material> MeshComponent::getMaterial() const
{
	return material;
}

void MeshComponent::initialize()
{
	updateMesh();
}

void MeshComponent::tick(float dt)
{
	meshRenderer->setWorldTransformationMatrix(getParent()->getWorldTransformationMatrix());
	getEngine()->getGraphics()->addToRenderQueue(meshRenderer);
}

void MeshComponent::updateMesh()
{
	meshRenderer = getEngine()->getGraphics()->createMeshRenderer(mesh, material);
}
