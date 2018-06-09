#pragma once

#include <functional>

#include "action.h"

class CallFunction : public Action
{
public:
	ACTION_BODY(CallFunction);

	explicit CallFunction(const std::function<void()>& function);
	virtual void operator()(SequenceInstance* sequenceInstance) override;
private:
	std::function<void()> function;
};