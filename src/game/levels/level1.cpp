#include "game/levels/level1.h"
#include "game/levels/level2.h"

void Level1::start()
{
	Level::start();
}

void Level1::tick(float dt)
{
	Level::tick(dt);
}

bool Level1::lost()
{
	return playerIsLowerThan(-20.0f);
}

std::wstring Level1::getTitle() const
{
	return L"前進";
}

std::shared_ptr<Scene> Level1::getNextScene() const
{
	return std::make_shared<Level2>();
}

std::string Level1::getLevelPath() const
{
	return "assets/models/levels/level1.fbx";
}
