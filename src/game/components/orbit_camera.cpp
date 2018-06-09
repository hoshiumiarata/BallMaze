#include "game/components/orbit_camera.h"

#include "engine/engine.h"
#include "engine/node.h"
#include "engine/camera.h"
#include "engine/components/camera_component.h"
#include "engine/components/dynamic_body_component.h"
#include "engine/subsystems/input/input_subsystem.h"
#include "engine/subsystems/physics/physics_subsystem.h"
#include "engine/subsystems/physics/physics_world.h"
#include "engine/subsystems/physics/hit_info.h"

#include <cmath>
#include <algorithm>

OrbitCamera::OrbitCamera(Node* target, float distance)
	: target(target), distance(distance)
{
}

void OrbitCamera::initialize()
{
	cameraComponent = getParent()->findComponent<CameraComponent>();
	camera = cameraComponent->getCamera().get();

	auto dynamicBodyComponent = target->findComponent<DynamicBodyComponent>();
	assert(dynamicBodyComponent != nullptr);
	targetBody = dynamicBodyComponent->getPhysicsBody().get();

	forwardAxis = getEngine()->getInput()->createAxis();
	forwardAxis->addMouseAxis(Mouse::Axis::Y, 0.04f);
	forwardAxis->addGamepadAxis(Gamepad::Axis::RightStickY);

	rightAxis = getEngine()->getInput()->createAxis();
	rightAxis->addMouseAxis(Mouse::Axis::X, 0.04f);
	rightAxis->addGamepadAxis(Gamepad::Axis::RightStickX);

	updateTransform();
}

void OrbitCamera::tick(float dt)
{
	yAngle -= rightAxis->getAxisValue() * dt;
	xAngle -= forwardAxis->getAxisValue() * dt;

	if (xAngle < -M_PI_2)
		xAngle = static_cast<float>(-M_PI_2);
	else if (xAngle > M_PI_2)
		xAngle = static_cast<float>(M_PI_2);

	updateTransform();

	vec3 targetPosition = target->getWorldTransform().position;

	cameraComponent->updateCamera();
	vec3 cameraDirection = getForwardVector();

	vec3 edges[5] = {
		camera->screenToWorld({ -1.0f, -1.0f }),
		camera->screenToWorld({ 1.0f, -1.0f }),
		camera->screenToWorld({ -1.0f, 1.0f }),
		camera->screenToWorld({ 1.0f, 1.0f }),
		camera->screenToWorld({ 0.0f, 0.0f })
	};

	float cameraShift = 0.0f;

	for (auto& edge : edges)
	{
		std::vector<HitInfo> hitInfos = getEngine()->getPhysics()->getPhysicsWorld()->rayCastAll(targetPosition, edge);

		for (const auto& hitInfo : hitInfos)
		{
			const bool ignored = std::find(ignoredBodies.begin(), ignoredBodies.end(), hitInfo.physicsBody) != ignoredBodies.end();
			if (ignored)
				continue;

			const float distanceToHit = targetPosition.distanceTo(hitInfo.point);
			if (distanceToHit > distance)
				continue;

			cameraShift = std::max(cameraShift, cameraDirection.dot(hitInfo.point - edge));
		}
	}

	cameraShift += defaultCameraShift;

	getParent()->updateWorldTransform([&](auto& transform) {
		transform.position = transform.position + cameraDirection * cameraShift;
	});

	cameraComponent->updateCamera();
}

void OrbitCamera::ignorePhysicsBody(PhysicsBody* body)
{
	ignoredBodies.push_back(body);
}

std::pair<vec3, vec3> OrbitCamera::getForwardRightVector() const
{
	vec3 forwardVector = getParent()->getWorldTransform().rotation.rotate({ 0.0f, 0.0f, -1.0f });
	forwardVector.normalize();

	vec3 rightVector = forwardVector.cross({ 0.0f, 1.0f, 0.0f });

	return std::make_pair(forwardVector, rightVector);
}

vec3 OrbitCamera::getForwardVector() const
{
	return getForwardRightVector().first;
}

vec3 OrbitCamera::getRightVector() const
{
	return getForwardRightVector().second;
}

void OrbitCamera::setAngleX(float x)
{
	xAngle = x;
}

void OrbitCamera::setAngleY(float y)
{
	yAngle = y;
}

void OrbitCamera::updateTransform()
{
	getParent()->updateWorldTransform([&](auto& transform) {
		vec3 targetWorldPosition = target->getWorldTransform().position;
		transform.rotation = Quaternion({ 0.0f, 1.0f, 0.0f }, yAngle);

		vec3 forwardVector = transform.rotation.rotate({ 0.0f, 0.0f, -1.0f });
		vec3 leftVector = vec3{ 0.0f, 1.0f, 0.0f }.cross(forwardVector);

		transform.rotation = Quaternion(leftVector, xAngle) * transform.rotation;
		transform.position = targetWorldPosition + transform.rotation.rotate({ 0.0f, 0.0f, distance });
	});
}
