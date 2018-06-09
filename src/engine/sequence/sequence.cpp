#include <algorithm>

#include "engine/sequence/sequence.h"
#include "engine/sequence/actions/action.h"

Sequence::Sequence() = default;

Sequence::Sequence(std::initializer_list<std::shared_ptr<Action>> actionList)
	: actions(actionList)
{
}

void Sequence::start(Engine* engine, Mode mode)
{
	std::vector<std::unique_ptr<Action>> copy(actions.size());

	std::transform(actions.begin(), actions.end(), copy.begin(), [](auto& action) -> auto {
		return action->clone();
	});

	auto sequenceInstance = std::make_unique<SequenceInstance>(engine, copy, mode == Mode::Looped);
	sequenceInstances.push_back(std::move(sequenceInstance));
}

void Sequence::stop()
{
	sequenceInstances.clear();
}
