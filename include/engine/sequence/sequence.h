#pragma once

#include <memory>
#include <initializer_list>
#include <vector>

#include "engine/sequence/sequence_instance.h"

class Engine;
class Action;

class Sequence
{
public:
	Sequence();
	Sequence(std::initializer_list<std::shared_ptr<Action>> actionList);

	enum class Mode {
		Single, Looped
	};

	void start(Engine* engine, Mode mode = Mode::Single);
	void stop();

private:
	std::vector<std::shared_ptr<Action>> actions;
	std::vector<std::unique_ptr<SequenceInstance>> sequenceInstances;
};