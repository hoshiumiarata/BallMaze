#pragma once

#include "../index_buffer.h"

#include <GL/glew.h>

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer();
	virtual ~OpenGLIndexBuffer() override;

	virtual void bind() override;
	virtual void setData(const std::vector<unsigned int>& data) override;

private:
	GLuint ibo;
};