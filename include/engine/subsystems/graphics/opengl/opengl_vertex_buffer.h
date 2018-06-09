#pragma once

#include "../vertex_buffer.h"

#include <GL/glew.h>

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	OpenGLVertexBuffer();
	virtual ~OpenGLVertexBuffer() override;

	virtual void bind() override;

	virtual void setData(const std::vector<vec2>& data) override;
	virtual void setData(const std::vector<vec3>& data) override;

private:
	template <typename T>
	void setOpenGLData(const T& data);

	GLuint vbo;
};
