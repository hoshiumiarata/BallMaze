#include "engine/sequence/sequence_instance.h"
#include "engine/sequence/actions/action.h"

SequenceInstance::SequenceInstance(Engine* engine, std::vector<std::unique_ptr<Action>>& actions, bool looped)
	: engine(engine), actions(std::move(actions)), looped(looped)
{
	for (auto& action : this->actions)
		action->setEngine(engine);

	next();
}

SequenceInstance::~SequenceInstance() = default;

void SequenceInstance::actionCompleted()
{
	next();
}

void SequenceInstance::next()
{
	if (nextAction >= actions.size())
	{
		if (looped && !actions.empty())
			nextAction = 0;
		else
		{
			actions.clear();
			return;
		}
	}

	auto& action = *actions[nextAction];
	nextAction++;
	action(this);
}
