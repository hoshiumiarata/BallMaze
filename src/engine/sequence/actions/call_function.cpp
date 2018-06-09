#include "engine/sequence/actions/call_function.h"

CallFunction::CallFunction(const std::function<void()>& function)
	: function(function)
{

}

void CallFunction::operator()(SequenceInstance* sequenceInstance)
{
	function();
	completed(sequenceInstance);
}
