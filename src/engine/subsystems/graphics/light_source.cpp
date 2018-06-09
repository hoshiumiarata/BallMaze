#include "engine/subsystems/graphics/light_source.h"

void LightSource::ambientLight(const vec4 & ambient)
{
	this->ambient = ambient;
}

void LightSource::directionalLight(const vec4 & ambient, const vec4 & diffuse, const vec4 & specular, const vec3 & direction)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->position = { direction.getX(), direction.getY(), direction.getZ(), 0.0f };
}

void LightSource::pointLight(const vec4 & ambient, const vec4 & diffuse, const vec4 & specular, const vec3 & position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation)
{
	this->ambient = ambient;
	this->diffuse = diffuse;
	this->specular = specular;
	this->position = { position.getX(), position.getY(), position.getZ(), 1.0f };
	this->constantAttenuation = constantAttenuation;
	this->linearAttenuation = linearAttenuation;
	this->quadraticAttenuation = quadraticAttenuation;
}
