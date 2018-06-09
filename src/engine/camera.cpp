#include "engine/camera.h"

#include <cmath>

const float Camera::getAspectRatio() const
{
	return aspectRatio;
}

void Camera::setAspectRatio(float newAspectRatio)
{
	if (std::fabs(aspectRatio - newAspectRatio) > 1e-5)
	{
		aspectRatio = newAspectRatio;
		updateProjectionMatrix();
	}
}

vec3 Camera::screenToWorld(const vec3& screen) const
{
	mat4 inversed = (projectionMatrix * viewMatrix).inversed();
	vec4 tmp = inversed * vec4{ screen.getX(), screen.getY(), screen.getZ(), 1.0f };
	return { tmp.getX() / tmp.getW(), tmp.getY() / tmp.getW(), tmp.getZ() / tmp.getW() };
}

vec3 Camera::worldToScreen(const vec3& world) const
{
	vec4 tmp = projectionMatrix * viewMatrix * vec4{ world.getX(), world.getY(), world.getZ(), 1.0f };
	return { tmp.getX() / tmp.getW(), tmp.getY() / tmp.getW(), tmp.getZ() / tmp.getW() };
}

const mat4& Camera::getProjectionMatrix() const
{
	return projectionMatrix;
}

const mat4& Camera::getViewMatrix() const
{
	return viewMatrix;
}

const Transform& Camera::getTransform() const
{
	return transform;
}

void Camera::setTransform(const Transform& transform)
{
	this->transform = transform;
	viewMatrix = transform.getTransformationMatrix().inversed();
}
