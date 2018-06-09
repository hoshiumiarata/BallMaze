#pragma once

#include <memory>

#include "engine/mixins/engine_access_mixin.h"

#define ACTION_BODY(CLASS) virtual std::unique_ptr<Action> clone() const override { return std::make_unique<CLASS>(*this); }

class SequenceInstance;

class Action : public EngineAccessMixin
{
public:
	virtual ~Action();

	virtual void operator()(SequenceInstance* sequenceInstance);

	virtual std::unique_ptr<Action> clone() const = 0;

protected:
	void completed(SequenceInstance* sequenceInstance);
};