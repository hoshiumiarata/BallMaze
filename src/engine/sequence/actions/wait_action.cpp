#include "engine/sequence/actions/wait_action.h"
#include "engine/engine.h"
#include "engine/timer.h"

WaitAction::WaitAction(float time)
	: time(time)
{

}

WaitAction::~WaitAction()
{
	if (timer)
		getEngine()->timerStop(timer);
}

void WaitAction::operator()(SequenceInstance* sequenceInstance)
{
	timer = std::make_shared<Timer>();
	timer->setInterval(time);
	timer->setLoopCount(1);
	timer->setAffectedByTimeScale(true);
	timer->setCallback([this, sequenceInstance](float dt) {
		completed(sequenceInstance);
	});
	getEngine()->timerStart(timer);
}