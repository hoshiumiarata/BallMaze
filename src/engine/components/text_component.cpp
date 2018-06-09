#include "engine/components/text_component.h"
#include "engine/engine.h"
#include "engine/node.h"
#include "engine/subsystems/graphics/graphics_subsystem.h"
#include "engine/subsystems/graphics/font.h"

TextComponent::TextComponent(const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<Font>& font)
	: shader(shader), font(font)
{
}

void TextComponent::initialize()
{
	texture = getEngine()->getGraphics()->createTexture();
	sprite = std::make_shared<Sprite>(shader, texture);
}

void TextComponent::setText(const std::wstring& text)
{
	font->setSize(size);
	font->renderText(texture, text);
	sprite->setSize(static_cast<float>(texture->getWidth()), static_cast<float>(texture->getHeight()));
}

void TextComponent::setVerticalAlign(Sprite::VerticalAlign verticalAlign)
{
	sprite->setVerticalAlign(verticalAlign);
}

void TextComponent::setHorizontalAlign(Sprite::HorizontalAlign horizontalAlign)
{
	sprite->setHorizontalAlign(horizontalAlign);
}

void TextComponent::setFontSize(unsigned int size)
{
	this->size = size;
}

void TextComponent::setAlpha(float alpha)
{
	sprite->setAlpha(alpha);
}

void TextComponent::tick(float dt)
{
	sprite->setTransform(getParent()->getWorldTransform());
	getEngine()->getGraphics()->addSpriteToRenderQueue(sprite);
}
