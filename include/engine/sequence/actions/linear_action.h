#pragma once

#include <functional>

#include "action.h"

class Timer;

class LinearAction : public Action
{
public:
	ACTION_BODY(LinearAction);

	LinearAction(float time, unsigned int division, float startValue, float endValue, const std::function<void(float)>& function);
	virtual ~LinearAction() override;
	virtual void operator()(SequenceInstance* sequenceInstance) override;
private:
	float time;
	unsigned int division;
	float startValue;
	float endValue;
	std::function<void(float)> function;
	std::shared_ptr<Timer> timer;
};