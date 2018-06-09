#include "game/levels/level5.h"
#include "game/levels/last_scene.h"

void Level5::start()
{
	Level::start();

	Node* kinematicFloorButton = getRoot().findChild("KinematicFloorButton", true);
	auto kinematicBodyComponent = kinematicFloorButton->findComponent<KinematicBodyComponent>();
	auto triggerComponent = kinematicFloorButton->addComponent<TriggerComponent>(kinematicBodyComponent->getPhysicsBody());
	floorButtonBody = kinematicBodyComponent->getPhysicsBody().get();

	Node* kinematicTrap = getRoot().findChild("KinematicTrap", true);
	trapBody = kinematicTrap->findComponent<KinematicBodyComponent>()->getPhysicsBody().get();

	Node* kinematicHiddenDoor = getRoot().findChild("KinematicHiddenDoor", true);
	hiddenDoorBody = kinematicHiddenDoor->findComponent<KinematicBodyComponent>()->getPhysicsBody().get();

	originalHiddenDoorPosition = hiddenDoorBody->getWorldTransform().position;
	originalFloorPosition = floorButtonBody->getWorldTransform().position;
	originalTrapRotation = trapBody->getWorldTransform().rotation;

	trapSequence = Sequence{
		std::make_shared<LinearAction>(0.5f, 50, 0.025f, -0.025f, [this](float v) {
			vec3 floor = originalFloorPosition;
			floor.setY(v);
			floorButtonBody->setPosition(floor);
		}),
		std::make_shared<WaitAction>(1.0f),
		std::make_shared<LinearAction>(0.5f, 50, 0.0f, 3.14159f / 2.0f, [this](float v) {
			trapBody->setRotation(Quaternion({ 1.0f, 0.0f, 0.0f }, v) * originalTrapRotation);
		}),
		std::make_shared<WaitAction>(1.0f),
		std::make_shared<LinearAction>(0.5f, 50, 5.0f, -5.0f, [=](float v) {
			vec3 hiddenDoor = originalHiddenDoorPosition;
			hiddenDoor.setY(v);
			hiddenDoorBody->setPosition(hiddenDoor);
		})
	};

	triggerComponent->addTrigger(playerPhysicsBody, [&]() {
		if (!trapActivated)
		{
			trapActivated = true;
			trapSequence.start(getEngine());
		}
	}, 0.1f);

	Node* deguchiText = getRoot().findChild("DeguchiText", true);
	auto meshComponent = deguchiText->findComponent<MeshComponent>();
	auto material = meshComponent->getMaterial();
	auto texture = getEngine()->getGraphics()->createTexture();
	font->setSize(100);
	font->renderText(texture, L"出口");
	material->setTexture(texture);
}

void Level5::tick(float dt)
{
	Level::tick(dt);
}

void Level5::resetLevel()
{
	Level::resetLevel();

	trapSequence.stop();

	trapActivated = false;
	hiddenDoorBody->setPosition(originalHiddenDoorPosition);
	floorButtonBody->setPosition(originalFloorPosition);
	trapBody->setRotation(originalTrapRotation);
}

bool Level5::lost()
{
	return playerIsLowerThan(-40.0f);
}

std::wstring Level5::getTitle() const
{
	return L"迷路";
}

std::shared_ptr<Scene> Level5::getNextScene() const
{
	return std::make_shared<LastScene>();
}

std::string Level5::getLevelPath() const
{
	return "assets/models/levels/level5.fbx";
}
