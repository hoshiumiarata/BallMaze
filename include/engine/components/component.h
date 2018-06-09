#pragma once

#include "../mixins/engine_access_mixin.h"

class Node;

class Component : public EngineAccessMixin
{
public:
	virtual ~Component();

	virtual void initialize() = 0;
	virtual void tick(float dt) = 0;

	Node* getParent() const;
	void setParent(Node* parent);
private:
	Node* parent = nullptr;
};