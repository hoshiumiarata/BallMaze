#include "engine/components/component.h"

Component::~Component() = default;

Node* Component::getParent() const
{
	return parent;
}

void Component::setParent(Node* parent)
{
	this->parent = parent;
}