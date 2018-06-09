#pragma once

#include "../texture.h"

#include <GL/glew.h>

class OpenGLTexture : public Texture
{
public:
	virtual ~OpenGLTexture() override;

	virtual void init(unsigned int width, unsigned int height) override;
	virtual void setData(unsigned int x, unsigned int y, unsigned int width, unsigned int height, DataFormat format, const uint8_t* data) override;
	virtual void bind() override;
private:
	GLuint tex = 0;
};