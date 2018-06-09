#include "engine/subsystems/graphics/sprite.h"

Sprite::Sprite(const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<Texture>& texture)
	: shader(shader), texture(texture)
{

}

std::shared_ptr<ShaderProgram> Sprite::getShader() const
{
	return shader;
}

std::shared_ptr<Texture> Sprite::getTexture() const
{
	return texture;
}

void Sprite::setSize(float width, float height)
{
	this->width = width;
	this->height = height;
}

float Sprite::getWidth() const
{
	return width;
}

void Sprite::setWidth(float width, bool saveAspectRatio)
{
	if (saveAspectRatio)
	{
		float aspect = this->height / this->width;
		this->height = width * aspect;
	}
	this->width = width;
}

float Sprite::getHeight() const
{
	return height;
}

void Sprite::setHeight(float height, bool saveAspectRatio)
{
	if (saveAspectRatio)
	{
		float aspect = this->width / this->height;
		this->width = height * aspect;
	}
	this->height = height;
}

Sprite::VerticalAlign Sprite::getVerticalAlign() const
{
	return verticalAlign;
}

void Sprite::setVerticalAlign(VerticalAlign verticalAlign)
{
	this->verticalAlign = verticalAlign;
}

Sprite::HorizontalAlign Sprite::getHorizontalAlign() const
{
	return horizontalAlign;
}

void Sprite::setHorizontalAlign(HorizontalAlign horizontalAlign)
{
	this->horizontalAlign = horizontalAlign;
}

const Transform& Sprite::getTransform() const
{
	return transform;
}

void Sprite::setTransform(const Transform& transform)
{
	this->transform = transform;
}

const vec4& Sprite::getColor() const
{
	return color;
}

void Sprite::setColor(const vec4& color)
{
	this->color = color;
}


void Sprite::setAlpha(float alpha)
{
	this->color.setW(alpha);
}