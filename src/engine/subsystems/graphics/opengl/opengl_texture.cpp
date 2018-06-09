#include "engine/subsystems/graphics/opengl/opengl_texture.h"

#include <cassert>

OpenGLTexture::~OpenGLTexture()
{
	if (tex)
		glDeleteTextures(1, &tex);
}

void OpenGLTexture::init(unsigned int width, unsigned int height)
{
	this->width = width;
	this->height = height;

	if (tex == 0)
		glGenTextures(1, &tex);

	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
}

void OpenGLTexture::setData(unsigned int x, unsigned int y, unsigned int width, unsigned int height, DataFormat format, const uint8_t * data)
{
	assert(tex);
	bind();

	GLenum glformat;
	GLenum type = GL_UNSIGNED_BYTE;

	switch (format)
	{
	case DataFormat::R:
		glformat = GL_RED;
		break;
	case DataFormat::RG:
		glformat = GL_RG;
		break;
	case DataFormat::RGB:
		glformat = GL_RGB;
		break;
	case DataFormat::RGBA:
		glformat = GL_RGBA;
		break;
	case DataFormat::BGR:
		glformat = GL_BGR;
		break;
	case DataFormat::BGRA:
		glformat = GL_BGRA;
		break;
	}
	glTexSubImage2D(GL_TEXTURE_2D, 0, x, y, width, height, glformat, type, data);
}

void OpenGLTexture::bind()
{
	assert(tex);
	glBindTexture(GL_TEXTURE_2D, tex);
}
