#include "game/game.h"

#include "game/levels/level1.h"

Game::Game()
{
	initializeEngine();
	start();
}

void Game::initializeEngine()
{
	engine.addSubSystem(new FileManagerSubSystem);
	engine.addSubSystem(new BulletPhysicsSubSustem);
	engine.addSubSystem(new GLFWWindowManagerSubSystem(1024, 768));
	engine.addSubSystem(new GLFWInputSubSystem);
	engine.addSubSystem(new OpenGLGraphicsSubSystem);
	engine.addSubSystem(new SceneManagerSubSystem);

	engine.setCamera(std::make_shared<PerspectiveCamera>(60.0f, 0.1f, 100000.0f));
}

void Game::start()
{
	engine.getSceneManager()->setScene(std::make_shared<Level1>());
	engine.start();
}
