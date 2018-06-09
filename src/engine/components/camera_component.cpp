#include "engine/components/camera_component.h"
#include "engine/node.h"
#include "engine/engine.h"
#include "engine/subsystems/window_manager/window_manager_subsystem.h"

CameraComponent::CameraComponent(const std::shared_ptr<Camera>& camera)
	: camera(camera)
{

}

std::shared_ptr<Camera> CameraComponent::getCamera() const
{
	return camera;
}

void CameraComponent::initialize()
{

}

void CameraComponent::tick(float dt)
{
	updateCamera();
}

void CameraComponent::updateCamera()
{
	camera->setAspectRatio(getEngine()->getWindowManager()->getAspectRatio());
	camera->setTransform(getParent()->getWorldTransform());
}
