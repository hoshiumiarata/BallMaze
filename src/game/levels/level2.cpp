#include "game/levels/level2.h"
#include "game/levels/level3.h"

void Level2::start()
{
	Level::start();

	for (unsigned int i = 1; i <= 5; i++)
	{
		Node* enemyBall = getRoot().findChild("DynamicEnemyBall" + std::to_string(i), true);
		Transform worldTransform = enemyBall->getWorldTransform();
		auto physicsBody = physicsWorld->createPhysicsBody(getEngine()->getPhysics()->createSphereShape(1.0f), worldTransform.position, worldTransform.rotation, 10000.0f);

		auto light = std::make_shared<LightSource>();

		vec4 color;

		switch (i)
		{
		case 1: color = { 1.0f, 0.0f, 0.0f, 1.0f }; break;
		case 2: color = { 0.0f, 1.0f, 0.0f, 1.0f }; break;
		case 3: color = { 0.0f, 0.0f, 1.0f, 1.0f }; break;
		case 4: color = { 1.0f, 0.0f, 1.0f, 1.0f }; break;
		case 5: color = { 0.0f, 1.0f, 1.0f, 1.0f }; break;
		}

		light->pointLight(color, color, color, vec3(), 1.0f, 0.0f, 0.1f);
		enemyBall->addComponent<LightComponent>(std::move(light));

		Node* enemyBallSocket = getRoot().findChild("EnemyBall" + std::to_string(i) + "Socket", true);
		Transform socketWorldTransform = enemyBallSocket->getWorldTransform();
		auto socketPhysicsBody = physicsWorld->createPhysicsBody(getEngine()->getPhysics()->createEmptyShape(), socketWorldTransform.position, socketWorldTransform.rotation, 0.0f);

		float d;

		if (i == 1 || i == 4 || i == 5)
			d = -5.0f;
		else if (i == 2)
			d = -3.0f;
		else if (i == 3)
			d = -2.0f;

		auto constraint = physicsWorld->createPointConstraint(physicsBody, socketPhysicsBody, { d, 0.0f, 0.0f }, vec3());

		orbitCamera->ignorePhysicsBody(physicsBody.get());

		enemyBall->addComponent<DynamicBodyComponent>(std::move(physicsBody));
		enemyBallSocket->addComponent<StaticBodyComponent>(std::move(socketPhysicsBody));

		enemyBall->addComponent<ConstraintComponent>(constraint);
	}
}

void Level2::tick(float dt)
{
	Level::tick(dt);
}

bool Level2::lost()
{
	return playerIsLowerThan(-10.0f);
}

std::wstring Level2::getTitle() const
{
	return L"ディスコ";
}

std::shared_ptr<Scene> Level2::getNextScene() const
{
	return std::make_shared<Level3>();
}

std::string Level2::getLevelPath() const
{
	return "assets/models/levels/level2.fbx";
}
