#pragma once

#include <memory>

#include "component.h"

class Sprite;

class SpriteComponent : public Component
{
public:
	explicit SpriteComponent(const std::shared_ptr<Sprite>& sprite);

	virtual void initialize() override;
	virtual void tick(float dt) override;
private:
	std::shared_ptr<Sprite> sprite;
};

