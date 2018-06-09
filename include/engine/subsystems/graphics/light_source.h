#pragma once

#include "engine/math/vector.h"

struct LightSource
{
	void ambientLight(const vec4& ambient);
	void directionalLight(const vec4& ambient, const vec4& diffuse, const vec4& specular, const vec3& direction);
	void pointLight(const vec4& ambient, const vec4& diffuse, const vec4& specular, const vec3& position, float constantAttenuation, float linearAttenuation, float quadraticAttenuation);

	vec4 ambient = { 0, 0, 0, 1 };
	vec4 diffuse = { 0, 0, 0, 1 };
	vec4 specular = { 0, 0, 0, 1 };
	vec4 position = { 0, 0, 0, 0 };
	vec4 emission = { 0, 0, 0, 0 };
	float constantAttenuation = 1.0f;
	float linearAttenuation = 0.0f;
	float quadraticAttenuation = 0.0f;
};