#pragma once

#include <string>

#include "../mixins/engine_access_mixin.h"

class ISubSystem : public EngineAccessMixin
{
public:
	virtual ~ISubSystem() {};

	virtual bool init() = 0;
	virtual bool update(float dt) = 0;
	virtual bool postUpdate() = 0;
	virtual bool destroy() = 0;

	virtual const std::string getName() const = 0;
};