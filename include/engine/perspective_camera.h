#pragma once

#include "camera.h"

class PerspectiveCamera : public Camera
{
public:
	PerspectiveCamera(float fov, float near, float far);

	virtual void updateProjectionMatrix() override;
private:
	float fov;
	float near;
	float far;
};