#include "engine/subsystems/graphics/material.h"

Material::Material(const std::shared_ptr<ShaderProgram>& shader)
	: shader(shader)
{

}

Material::~Material() = default;

void Material::setShader(const std::shared_ptr<ShaderProgram>& shader)
{
	this->shader = shader;
}

std::shared_ptr<ShaderProgram> Material::getShader() const
{
	return shader;
}

std::shared_ptr<Texture> Material::getTexture() const
{
	return texture;
}

void Material::setTexture(const std::shared_ptr<Texture>& texture)
{
	this->texture = texture;
}

const vec4& Material::getAmbient() const
{
	return ambient;
}

void Material::setAmbient(const vec4& ambient)
{
	this->ambient = ambient;
}

const vec4 & Material::getDiffuse() const
{
	return diffuse;
}

void Material::setDiffuse(const vec4 & diffuse)
{
	this->diffuse = diffuse;
}

const vec4& Material::getSpecular() const
{
	return specular;
}

void Material::setSpecular(const vec4& specular)
{
	this->specular = specular;
}

const vec4& Material::getEmission() const
{
	return emission;
}

void Material::setEmission(const vec4& emission)
{
	this->emission = emission;
}

float Material::getShininess() const
{
	return shininess;
}

void Material::setShininess(float shininess)
{
	this->shininess = shininess;
}
