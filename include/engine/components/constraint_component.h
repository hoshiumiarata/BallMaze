#pragma once

#include <memory>

#include "component.h"

class Constraint;

class ConstraintComponent : public Component
{
public:
	explicit ConstraintComponent(const std::shared_ptr<Constraint>& constraint);
	~ConstraintComponent();

	virtual void initialize() override;
	virtual void tick(float dt) override;

private:
	std::shared_ptr<Constraint> constraint;
};