#include "engine/subsystems/graphics/mesh_renderer.h"
#include "engine/subsystems/graphics/graphics_subsystem.h"
#include "engine/subsystems/graphics/material.h"
#include "engine/subsystems/graphics/index_buffer.h"
#include "engine/subsystems/graphics/vertex_buffer.h"
#include "engine/mesh.h"

MeshRenderer::MeshRenderer(GraphicsSubSystem* graphics, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material)
	: graphics(graphics),
	  mesh(mesh),
	  material(material),
	  verticesBuffer(graphics->createVertexBuffer()),
	  normalsBuffer(graphics->createVertexBuffer()),
      indicesBuffer(graphics->createIndexBuffer())
{
	verticesBuffer->setData(mesh->getVertices());
	normalsBuffer->setData(mesh->getNormals());
	indicesBuffer->setData(mesh->getIndices());

	if (!mesh->getTexCoords().empty())
	{
		texCoordsBuffer = graphics->createVertexBuffer();
		texCoordsBuffer->setData(mesh->getTexCoords());
	}
}

MeshRenderer::~MeshRenderer() = default;

std::shared_ptr<Mesh> MeshRenderer::getMesh() const
{
	return mesh;
}

std::shared_ptr<Material> MeshRenderer::getMaterial() const
{
	return material;
}

const mat4& MeshRenderer::getWorldTransformationMatrix() const
{
	return worldTransformationMatrix;
}

void MeshRenderer::setWorldTransformationMatrix(const mat4& matrix)
{
	worldTransformationMatrix = matrix;
}

VertexBuffer* MeshRenderer::getVerticesBuffer() const
{
	return verticesBuffer.get();
}

VertexBuffer* MeshRenderer::getNormalsBuffer() const
{
	return normalsBuffer.get();
}

IndexBuffer* MeshRenderer::getIndicesBuffer() const
{
	return indicesBuffer.get();
}

VertexBuffer* MeshRenderer::getTexCoordsBuffer() const
{
	return texCoordsBuffer.get();
}
