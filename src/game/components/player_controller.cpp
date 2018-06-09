#include "game/components/player_controller.h"

#include "engine/engine.h"
#include "engine/node.h"
#include "engine/components/dynamic_body_component.h"
#include "engine/subsystems/input/input_subsystem.h"
#include "engine/subsystems/physics/physics_body.h"
#include "engine/math/vector.h"

#include "game/components/orbit_camera.h"

#include <cassert>

PlayerController::PlayerController(OrbitCamera * orbitCamera, float speed)
	: orbitCamera(orbitCamera), speed(speed)
{

}

void PlayerController::initialize()
{
	auto dynamicBodyComponent = getParent()->findComponent<DynamicBodyComponent>();
	assert(dynamicBodyComponent != nullptr);
	body = dynamicBodyComponent->getPhysicsBody().get();

	forwardAxis = getEngine()->getInput()->createAxis();
	forwardAxis->addKeyboardKey(Keyboard::Key::W, 1.0f);
	forwardAxis->addKeyboardKey(Keyboard::Key::S, -1.0f);
	forwardAxis->addKeyboardKey(Keyboard::Key::Up, 1.0f);
	forwardAxis->addKeyboardKey(Keyboard::Key::Down, -1.0f);
	forwardAxis->addGamepadAxis(Gamepad::Axis::LeftStickY);

	rightAxis = getEngine()->getInput()->createAxis();
	rightAxis->addKeyboardKey(Keyboard::Key::D, 1.0f);
	rightAxis->addKeyboardKey(Keyboard::Key::A, -1.0f);
	rightAxis->addKeyboardKey(Keyboard::Key::Right, 1.0f);
	rightAxis->addKeyboardKey(Keyboard::Key::Left, -1.0f);
	rightAxis->addGamepadAxis(Gamepad::Axis::LeftStickX);
}

void PlayerController::tick(float dt)
{
	if (forwardAxis->getAxisValue() != 0.0f || rightAxis->getAxisValue() != 0.0f)
	{
		auto fr = orbitCamera->getForwardRightVector();
		vec3& forward = fr.first;
		forward.setY(0);
		forward.normalize();
		vec3& right = fr.second;
		right.setY(0);
		right.normalize();
		float axisLength = std::sqrt(forwardAxis->getAxisValue() * forwardAxis->getAxisValue() + rightAxis->getAxisValue() * rightAxis->getAxisValue());
		body->applyCentralForce((forward * (forwardAxis->getAxisValue() / axisLength) + right * (rightAxis->getAxisValue() / axisLength)) * speed);
	}
}
