#include "engine/subsystems/graphics/opengl/opengl_index_buffer.h"

OpenGLIndexBuffer::OpenGLIndexBuffer()
{
	glGenBuffers(1, &ibo);
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &ibo);
}

void OpenGLIndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void OpenGLIndexBuffer::setData(const std::vector<unsigned int>& data)
{
	if (data.empty())
		return;

	bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(decltype(data.back())), &data[0], GL_STATIC_DRAW);
}
