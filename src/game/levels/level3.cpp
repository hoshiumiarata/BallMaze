#include "game/levels/level3.h"
#include "game/levels/level4.h"

void Level3::start()
{
	Level::start();

	for (unsigned int i = 0; i < 2; i++)
	{
		Node* platform = getRoot().findChild("KinematicCube" + std::to_string(i + 1), true);
		auto kinematicBody = platform->findComponent<KinematicBodyComponent>();

		PhysicsBody* body = kinematicBody->getPhysicsBody().get();
		Transform originalTransform = body->getWorldTransform();

		float a = i == 0 ? -1.0f : 1.0f;
		float b = -a;
		float time = 2.0f;
		unsigned int d = 100;

		rotateSeq[i] = Sequence{
			std::make_shared<LinearAction>(time, d, a, b, [=](float t) {
				body->setRotation(Quaternion({ 0.0f, 0.0f, 1.0f }, t) * originalTransform.rotation);
			}),
			std::make_shared<LinearAction>(time, d, b, a, [=](float t) {
				body->setRotation(Quaternion({ 0.0f, 0.0f, 1.0f }, t) * originalTransform.rotation);
			})
		};

		rotateSeq[i].start(getEngine(), Sequence::Mode::Looped);
	}
}

void Level3::tick(float dt)
{
	Level::tick(dt);
}

bool Level3::lost()
{
	return playerIsLowerThan(-5.0f);
}

std::wstring Level3::getTitle() const
{
	return L"逆行";
}

std::shared_ptr<Scene> Level3::getNextScene() const
{
	return std::make_shared<Level4>();
}

std::string Level3::getLevelPath() const
{
	return "assets/models/levels/level3.fbx";
}
