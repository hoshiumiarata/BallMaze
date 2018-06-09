#pragma once

#include <GL/glew.h>

class OpenGLVertexArrayBuffer
{
public:
	OpenGLVertexArrayBuffer();
	~OpenGLVertexArrayBuffer();

	void bind();

	void enableAttribute(GLuint index, GLint size);
	void diableAttribute(GLuint index);
private:
	GLuint vao;
};