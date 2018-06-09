#pragma once

#include "node.h"
#include "mixins/engine_access_mixin.h"

class Scene : public EngineAccessMixin
{
public:
	virtual ~Scene();;

	virtual void start();
	virtual void tick(float dt);
	virtual void end();

	Node& getRoot();

private:
	Node root;
};