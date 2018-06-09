#include "engine/subsystems/graphics/texture.h"

Texture::~Texture() = default;

unsigned int Texture::getWidth() const
{
	return width;
}

unsigned int Texture::getHeight() const
{
	return height;
}
