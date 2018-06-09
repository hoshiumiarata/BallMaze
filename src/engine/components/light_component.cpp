#include "engine/components/light_component.h"
#include "engine/node.h"
#include "engine/engine.h"
#include "engine/subsystems/graphics/graphics_subsystem.h"
#include "engine/subsystems/graphics/light_source.h"

LightComponent::LightComponent(const std::shared_ptr<LightSource>& lightSource)
	: lightSource(lightSource)
{

}

void LightComponent::initialize()
{
	originalPosition = lightSource->position;
	originalLinearAttenuation = lightSource->linearAttenuation;
	originalQuadraticAttenuation = lightSource->quadraticAttenuation;
}

void LightComponent::tick(float dt)
{
	Transform worldTransform = getParent()->getWorldTransform();
	if (lightSource->position.getW() > 1e-5)
	{
		for (size_t i = 0; i < 3; i++)
			lightSource->position.set(i, worldTransform.position.get(i));

		lightSource->position.setW(1.0f);
	}
	else
	{
		lightSource->position = worldTransform.getRotationMatrix() * originalPosition;
	}

	float averageScale = worldTransform.scale.average();
	lightSource->linearAttenuation = originalLinearAttenuation / averageScale;
	lightSource->quadraticAttenuation = originalQuadraticAttenuation / (averageScale * averageScale);

	getEngine()->getGraphics()->addLightSource(lightSource);
}
