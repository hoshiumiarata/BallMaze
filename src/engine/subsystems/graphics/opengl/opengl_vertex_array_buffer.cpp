#include "engine/subsystems/graphics/opengl/opengl_vertex_array_buffer.h"

OpenGLVertexArrayBuffer::OpenGLVertexArrayBuffer()
{
	glGenVertexArrays(1, &vao);
}

OpenGLVertexArrayBuffer::~OpenGLVertexArrayBuffer()
{
	glDeleteVertexArrays(1, &vao);
}

void OpenGLVertexArrayBuffer::bind()
{
	glBindVertexArray(vao);
}

void OpenGLVertexArrayBuffer::enableAttribute(GLuint index, GLint size)
{
	bind();

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, 0, nullptr);
}

void OpenGLVertexArrayBuffer::diableAttribute(GLuint index)
{
	bind();

	glDisableVertexAttribArray(index);
}
