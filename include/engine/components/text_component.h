#pragma once

#include <memory>
#include <string>

#include "component.h"
#include "../subsystems/graphics/sprite.h"

class ShaderProgram;
class Font;
class Texture;

class TextComponent : public Component
{
public:
	TextComponent(const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<Font>& font);

	virtual void initialize() override;

	void setText(const std::wstring& text);
	void setVerticalAlign(Sprite::VerticalAlign verticalAlign);
	void setHorizontalAlign(Sprite::HorizontalAlign horizontalAlign);
	void setFontSize(unsigned int size);
	void setAlpha(float alpha);
	virtual void tick(float dt) override;
private:
	std::shared_ptr<ShaderProgram> shader;
	std::shared_ptr<Font> font;
	std::shared_ptr<Sprite> sprite;
	std::shared_ptr<Texture> texture;

	unsigned int size = 48;
};

