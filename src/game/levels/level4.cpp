#include "game/levels/level4.h"
#include "game/levels/level5.h"

void Level4::start()
{
	Level::start();

	for (unsigned int i = 0; i < 2; i++)
	{
		Node* platform = getRoot().findChild("KinematicCube" + std::to_string(i + 1), true);
		auto kinematicBody = platform->findComponent<KinematicBodyComponent>();
		bodies[i] = kinematicBody->getPhysicsBody().get();
	}
}

void Level4::tick(float dt)
{
	Level::tick(dt);

	Quaternion rot({ 0.0f, 1.0f, 0.0f }, dt);

	for (auto& body : bodies)
	{
		body->setRotation(rot * body->getWorldTransform().rotation);
	}
}

bool Level4::lost()
{
	return playerIsLowerThan(-5.0f);
}

std::wstring Level4::getTitle() const
{
	return L"創造力不足";
}

std::shared_ptr<Scene> Level4::getNextScene() const
{
	return std::make_shared<Level5>();
}

std::string Level4::getLevelPath() const
{
	return "assets/models/levels/level4.fbx";
}
