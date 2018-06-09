#pragma once

#include <memory>

#include "engine/math/vector.h"

class ShaderProgram;
class Texture;

class Material
{
public:
	explicit Material(const std::shared_ptr<ShaderProgram>& shader);
	~Material();

	void setShader(const std::shared_ptr<ShaderProgram>& shader);
	std::shared_ptr<ShaderProgram> getShader() const;

	std::shared_ptr<Texture> getTexture() const;
	void setTexture(const std::shared_ptr<Texture>& texture);

	const vec4& getAmbient() const;
	void setAmbient(const vec4& ambient);

	const vec4& getDiffuse() const;
	void setDiffuse(const vec4& diffuse);

	const vec4& getSpecular() const;
	void setSpecular(const vec4& specular);

	const vec4& getEmission() const;
	void setEmission(const vec4& emission);

	float getShininess() const;
	void setShininess(float shininess);

private:
	std::shared_ptr<ShaderProgram> shader;
	std::shared_ptr<Texture> texture;

	vec4 ambient = { 0.2f, 0.2f, 0.2f, 1.0f };
	vec4 diffuse = { 0.8f, 0.8f, 0.8f, 1.0f };
	vec4 specular = { 0.0f, 0.0f, 0.0f, 1.0f };
	vec4 emission = { 0.0f, 0.0f, 0.0f, 1.0f };
	float shininess = 0.0f;
};