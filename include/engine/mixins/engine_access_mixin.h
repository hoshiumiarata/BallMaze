#pragma once

class Engine;

class EngineAccessMixin
{
public:
	void setEngine(Engine* engine);
	Engine* getEngine();
private:
	Engine* engine = nullptr;
};

inline void EngineAccessMixin::setEngine(Engine* engine)
{
	this->engine = engine;
}

inline Engine* EngineAccessMixin::getEngine()
{
	return engine;
}