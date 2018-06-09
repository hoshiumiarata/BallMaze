#include "engine/perspective_camera.h"

#include <cmath>

PerspectiveCamera::PerspectiveCamera(float fov, float near, float far)
	: fov(fov), near(near), far(far)
{
	updateProjectionMatrix();
}


void PerspectiveCamera::updateProjectionMatrix()
{
	const float fovRad = fov / 180.0f * static_cast<float>(M_PI);
	const float tanFov2 = std::tan(fovRad / 2.0f);
	projectionMatrix.set({
		{ 1.0f / (aspectRatio * tanFov2), 0.0f,           0.0f,                         0.0f },
		{ 0.0f,                           1.0f / tanFov2, 0.0f,                         0.0f },
		{ 0.0f,                           0.0f,           -(far + near) / (far - near), -2.0f * far * near / (far - near) },
		{ 0.0f,                           0.0f,           -1.0f,                        0.0f }
	});
}
