#pragma once

#include <memory>

#include "engine/math/transform.h"

class Texture;
class ShaderProgram;

class Sprite
{
public:
	Sprite(const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<Texture>& texture);

	std::shared_ptr<ShaderProgram> getShader() const;
	std::shared_ptr<Texture> getTexture() const;

	void setSize(float width, float height);
	float getWidth() const;
	void setWidth(float width, bool saveAspectRatio = true);
	float getHeight() const;
	void setHeight(float height, bool saveAspectRatio = true);

	enum class VerticalAlign { Top, Center, Bottom };
	VerticalAlign getVerticalAlign() const;
	void setVerticalAlign(VerticalAlign verticalAlign);

	enum class HorizontalAlign { Left, Center, Right };
	HorizontalAlign getHorizontalAlign() const;
	void setHorizontalAlign(HorizontalAlign horizontalAlign);

	const Transform& getTransform() const;
	void setTransform(const Transform& transform);

	const vec4& getColor() const;
	void setColor(const vec4& color);
	void setAlpha(float alpha);
private:
	std::shared_ptr<ShaderProgram> shader;
	std::shared_ptr<Texture> texture;
	float width = 0.0f;
	float height = 0.0f;
	VerticalAlign verticalAlign = VerticalAlign::Top;
	HorizontalAlign horizontalAlign = HorizontalAlign::Left;

	vec4 color = { 1.0f, 1.0f, 1.0f, 1.0f };
	Transform transform;
};

