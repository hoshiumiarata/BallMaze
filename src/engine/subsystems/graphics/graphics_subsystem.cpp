#include "engine/subsystems/graphics/graphics_subsystem.h"

void GraphicsSubSystem::addToRenderQueue(const std::weak_ptr<MeshRenderer>& meshRenderer)
{
	renderQueue.push_back(meshRenderer);
}

void GraphicsSubSystem::addSpriteToRenderQueue(const std::weak_ptr<Sprite>& sprite)
{
	spriteRenderQueue.push_back(sprite);
}

void GraphicsSubSystem::addLightSource(const std::weak_ptr<LightSource>& lightSource)
{
	lightSources.push_back(lightSource);
}
