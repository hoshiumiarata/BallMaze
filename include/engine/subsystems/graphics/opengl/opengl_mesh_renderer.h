#pragma once

#include "../mesh_renderer.h"

class OpenGLVertexArrayBuffer;

class OpenGLMeshRenderer : public MeshRenderer
{
public:
	OpenGLMeshRenderer(GraphicsSubSystem* graphics, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material);

	OpenGLVertexArrayBuffer* getVertexArrayBuffer() const;
private:
	std::unique_ptr<OpenGLVertexArrayBuffer> vao;
};