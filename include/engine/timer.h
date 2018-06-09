#pragma once

#include <functional>

class Timer
{
public:
	void setInterval(float interval);
	void setLoopCount(unsigned int loopCount);
	void setAffectedByTimeScale(bool affectedByTimeScale);
	void setCallback(const std::function<void(float dt)>& callback);
	float getInterval() const;
	unsigned int getLoopCount() const;
	bool isAffectedByTimeScale() const;

	bool step(float dt, float timeScale = 1.0f);

private:
	float interval = 1.0f;
	unsigned int loopCount = 1;
	bool affectedByTimeScale = true;
	std::function<void(float dt)> callback;

	float time = 0.0f;
	unsigned int currentLoop = 0;
};

