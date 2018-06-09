#pragma once

#include <vector>
#include <memory>

class Action;
class Engine;

class SequenceInstance
{
public:
	SequenceInstance(Engine* engine, std::vector<std::unique_ptr<Action>>& actions, bool looped);
	~SequenceInstance();

	void actionCompleted();

private:
	void next();

	bool looped = false;

	Engine* engine;
	std::vector<std::unique_ptr<Action>> actions;
	size_t nextAction = 0;
};