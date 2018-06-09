#include "engine/scene.h"

Scene::~Scene() = default;

void Scene::start()
{
	root.setEngine(getEngine());
}

void Scene::tick(float dt)
{
	root.update(dt);
}

void Scene::end()
{

}

 Node& Scene::getRoot()
{
	return root;
}
