#pragma once

#include <memory>

#include "engine/math/matrix.h"

class GraphicsSubSystem;
class Mesh;
class Material;
class VertexBuffer;
class IndexBuffer;

class MeshRenderer
{
public:
	MeshRenderer(GraphicsSubSystem* graphics, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);
	virtual ~MeshRenderer();

	std::shared_ptr<Mesh> getMesh() const;
	std::shared_ptr<Material> getMaterial() const;
	
	const mat4& getWorldTransformationMatrix() const;
	void setWorldTransformationMatrix(const mat4& matrix);

	VertexBuffer* getVerticesBuffer() const;
	VertexBuffer* getNormalsBuffer() const;
	IndexBuffer* getIndicesBuffer() const;
	VertexBuffer* getTexCoordsBuffer() const;
protected:
	GraphicsSubSystem* graphics;
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;
	mat4 worldTransformationMatrix;

	std::unique_ptr<VertexBuffer> verticesBuffer;
	std::unique_ptr<VertexBuffer> normalsBuffer;
	std::unique_ptr<IndexBuffer> indicesBuffer;
	std::unique_ptr<VertexBuffer> texCoordsBuffer;
};