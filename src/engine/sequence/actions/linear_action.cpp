#include "engine/sequence/actions/linear_action.h"
#include "engine/engine.h"
#include "engine/timer.h"

LinearAction::LinearAction(float time, unsigned int division, float startValue, float endValue, const std::function<void(float)>& function)
	: time(time), division(division), startValue(startValue), endValue(endValue), function(function)
{

}

LinearAction::~LinearAction()
{
	if (timer)
		getEngine()->timerStop(timer);
}

void LinearAction::operator()(SequenceInstance* sequenceInstance)
{
	function(startValue);

	if (division == 0)
	{
		function(endValue);
		return;
	}

	timer = std::make_shared<Timer>();
	timer->setInterval(time / division);
	timer->setLoopCount(division);
	timer->setAffectedByTimeScale(true);
	unsigned int loop = 0;
	float step = (endValue - startValue) / division;
	timer->setCallback([this, sequenceInstance, loop, step](float dt) mutable {
		loop++;
		function(startValue + step * loop);

		if (loop == division)
			completed(sequenceInstance);
	});
	getEngine()->timerStart(timer);
}
