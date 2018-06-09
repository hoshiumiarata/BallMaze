#pragma once

#include <memory>
#include <vector>

#include "engine/components/component.h"
#include "engine/subsystems/input/input_axis.h"
#include "engine/math/vector.h"

class Camera;
class CameraComponent;
class Node;
class PhysicsBody;

class OrbitCamera : public Component
{
public:
	OrbitCamera(Node* target, float distance);

	virtual void initialize() override;
	virtual void tick(float dt) override;

	void ignorePhysicsBody(PhysicsBody* body);

	std::pair<vec3, vec3> getForwardRightVector() const;
	vec3 getForwardVector() const;
	vec3 getRightVector() const;

	void setAngleX(float x);
	void setAngleY(float y);
private:
	void updateTransform();

	std::unique_ptr<InputAxis> forwardAxis;
	std::unique_ptr<InputAxis> rightAxis;

	Node* target;
	float distance;

	float defaultCameraShift = 0.25f;
	float xAngle = 0.5f;
	float yAngle = 0.0f;

	Camera* camera = nullptr;
	CameraComponent* cameraComponent = nullptr;
	PhysicsBody* targetBody = nullptr;

	std::vector<PhysicsBody*> ignoredBodies;
};

