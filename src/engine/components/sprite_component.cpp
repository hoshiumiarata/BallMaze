#include "engine/components/sprite_component.h"
#include "engine/engine.h"
#include "engine/node.h"
#include "engine/subsystems/graphics/graphics_subsystem.h"
#include "engine/subsystems/graphics/sprite.h"

SpriteComponent::SpriteComponent(const std::shared_ptr<Sprite>& sprite)
	: sprite(sprite)
{

}

void SpriteComponent::initialize()
{

}

void SpriteComponent::tick(float dt)
{
	sprite->setTransform(getParent()->getWorldTransform());
	getEngine()->getGraphics()->addSpriteToRenderQueue(sprite);
}
