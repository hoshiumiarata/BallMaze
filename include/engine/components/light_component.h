#pragma once

#include <memory>

#include "component.h"

#include "../math/vector.h"

struct LightSource;

class LightComponent : public Component
{
public:
	explicit LightComponent(const std::shared_ptr<LightSource>& lightSource);

	virtual void initialize() override;
	virtual void tick(float dt) override;
private:
	std::shared_ptr<LightSource> lightSource;
	vec4 originalPosition;
	float originalLinearAttenuation = 0.0f;
	float originalQuadraticAttenuation = 0.0f;
};