#include "engine/components/constraint_component.h"

ConstraintComponent::ConstraintComponent(const std::shared_ptr<Constraint>& constraint)
	: constraint(constraint)
{
}

ConstraintComponent::~ConstraintComponent() = default;

void ConstraintComponent::initialize()
{
}

void ConstraintComponent::tick(float dt)
{
}
