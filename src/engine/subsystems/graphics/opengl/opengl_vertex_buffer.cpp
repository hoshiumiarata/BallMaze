#include "engine/subsystems/graphics/opengl/opengl_vertex_buffer.h"

OpenGLVertexBuffer::OpenGLVertexBuffer()
{
	glGenBuffers(1, &vbo);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &vbo);
}

void OpenGLVertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void OpenGLVertexBuffer::setData(const std::vector<vec3>& data)
{
	setOpenGLData(data);
}

void OpenGLVertexBuffer::setData(const std::vector<vec2>& data)
{
	setOpenGLData(data);
}

template<typename T>
void OpenGLVertexBuffer::setOpenGLData(const T & data)
{
	if (data.empty())
		return;

	bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(decltype(data.back())), &data[0], GL_STATIC_DRAW);
}