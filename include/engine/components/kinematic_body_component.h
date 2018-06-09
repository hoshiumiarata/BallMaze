#pragma once

#include <memory>

#include "dynamic_body_component.h"

class KinematicBodyComponent : public DynamicBodyComponent
{
public:
	using DynamicBodyComponent::DynamicBodyComponent;
	virtual void initialize() override;
};

