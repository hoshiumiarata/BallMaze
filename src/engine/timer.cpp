#include "engine/timer.h"

void Timer::setInterval(float interval)
{
	this->interval = interval;
}

void Timer::setLoopCount(unsigned int loopCount)
{
	this->loopCount = loopCount;
}

void Timer::setAffectedByTimeScale(bool affectedByTimeScale)
{
	this->affectedByTimeScale = affectedByTimeScale;
}

void Timer::setCallback(const std::function<void(float dt)>& callback)
{
	this->callback = callback;
}

float Timer::getInterval() const
{
	return interval;
}

unsigned int Timer::getLoopCount() const
{
	return loopCount;
}

bool Timer::isAffectedByTimeScale() const
{
	return affectedByTimeScale;
}

bool Timer::step(float dt, float timeScale)
{
	if (affectedByTimeScale)
		dt *= timeScale;

	time += dt;

	if (time >= interval)
	{
		callback(time);
		if (loopCount)
		{
			currentLoop++;
			if (currentLoop >= loopCount)
				return true;
		}
		time = 0.0f;
	}

	return false;
}
