#include "engine/sequence/sequence_instance.h"
#include "engine/sequence/actions/action.h"

Action::~Action() = default;

void Action::completed(SequenceInstance* sequenceInstance)
{
	sequenceInstance->actionCompleted();
}

void Action::operator()(SequenceInstance* sequenceInstance)
{
	completed(sequenceInstance);
}