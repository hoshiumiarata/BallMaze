#pragma once

#include <memory>
#include <vector>

#include "engine.h"

class Game
{
public:
	Game();
private:
	void initializeEngine();
	void start();

	Engine engine;
};