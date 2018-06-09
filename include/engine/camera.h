#pragma once

#include "math/transform.h"
#include "math/matrix.h"

class Camera
{
public:
	const float getAspectRatio() const;
	void setAspectRatio(float newAspectRatio);

	vec3 screenToWorld(const vec3& screen) const;
	vec3 worldToScreen(const vec3& world) const;

	const mat4& getProjectionMatrix() const;
	const mat4& getViewMatrix() const;

	const Transform& getTransform() const;
	void setTransform(const Transform& transform);

	virtual void updateProjectionMatrix() = 0;
protected:
	float aspectRatio = 4.0f / 3.0f;

	mutable mat4 viewMatrix;
	mutable mat4 projectionMatrix;
private:
	Transform transform;
};