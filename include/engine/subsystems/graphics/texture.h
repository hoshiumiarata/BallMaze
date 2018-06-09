#pragma once

#include <vector>
#include <cstdint>

class Texture
{
public:
	enum class DataFormat
	{
		R, RG, RGB, RGBA, BGR, BGRA
	};

	virtual ~Texture();

	virtual void init(unsigned int width, unsigned int height) = 0;
	virtual void setData(unsigned int x, unsigned int y, unsigned int width, unsigned int height, DataFormat format, const uint8_t* data) = 0;

	virtual void bind() = 0;

	unsigned int getWidth() const;
	unsigned int getHeight() const;

protected:
	unsigned int width = 0;
	unsigned int height = 0;
};

