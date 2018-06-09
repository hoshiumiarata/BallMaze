#include "engine/subsystems/graphics/opengl/opengl_mesh_renderer.h"

#include "engine/subsystems/graphics/vertex_buffer.h"
#include "engine/subsystems/graphics/opengl/opengl_vertex_array_buffer.h"

OpenGLMeshRenderer::OpenGLMeshRenderer(GraphicsSubSystem* graphics, const std::shared_ptr<Mesh>& mesh, const std::shared_ptr<Material>& material)
	: MeshRenderer(graphics, mesh, material), vao(std::make_unique<OpenGLVertexArrayBuffer>())
{
	vao->bind();
	verticesBuffer->bind();
	vao->enableAttribute(0, 3);
	normalsBuffer->bind();
	vao->enableAttribute(1, 3);
	if (texCoordsBuffer)
	{
		texCoordsBuffer->bind();
		vao->enableAttribute(2, 2);
	}
}

OpenGLVertexArrayBuffer * OpenGLMeshRenderer::getVertexArrayBuffer() const
{
	return vao.get();
}
