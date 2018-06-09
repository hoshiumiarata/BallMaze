#pragma once

#include "action.h"

class Timer;

class WaitAction : public Action
{
public:
	ACTION_BODY(WaitAction);

	explicit WaitAction(float time);
	virtual ~WaitAction() override;

	virtual void operator()(SequenceInstance* sequenceInstance) override;
private:
	float time;
	std::shared_ptr<Timer> timer;
};