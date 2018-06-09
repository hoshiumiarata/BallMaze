#pragma once

#include "vector.h"
#include "matrix.h"
#include "quaternion.h"
#include <cmath>

class Transform
{
public:
	Transform(const vec3& position = { 0, 0, 0 }, const Quaternion& rotation = Quaternion(), const vec3& scale = { 1, 1, 1 })
		: position(position), rotation(rotation), scale(scale)
	{

	}

	Transform(const mat4& transformationMatrix)
	{
		position = { transformationMatrix.get(0, 3), transformationMatrix.get(1, 3), transformationMatrix.get(2, 3) };

		for (size_t i = 0; i < 3; i++)
		{
			auto a = transformationMatrix.get(0, i);
			auto b = transformationMatrix.get(1, i);
			auto c = transformationMatrix.get(2, i);
			scale.set(i, sqrt(a * a + b * b + c * c));
		}

		mat3 rotationMatrix = {
			{ transformationMatrix.get(0, 0) / scale.getX(), transformationMatrix.get(0, 1) / scale.getY(), transformationMatrix.get(0, 2) / scale.getZ() },
			{ transformationMatrix.get(1, 0) / scale.getX(), transformationMatrix.get(1, 1) / scale.getY(), transformationMatrix.get(1, 2) / scale.getZ() },
			{ transformationMatrix.get(2, 0) / scale.getX(), transformationMatrix.get(2, 1) / scale.getY(), transformationMatrix.get(2, 2) / scale.getZ() }
		};

		rotation = Quaternion(rotationMatrix);
	}

	vec3 position;
	Quaternion rotation;
	vec3 scale;

	mat4 getTransformationMatrix() const
	{
		return getPositionMatrix() * getRotationMatrix() * getScaleMatrix();
	}

	mat4 getPositionMatrix() const
	{
		return {
			{ 1.0f, 0.0f, 0.0f, position.getX() },
			{ 0.0f, 1.0f, 0.0f, position.getY() },
			{ 0.0f, 0.0f, 1.0f, position.getZ() },
			{ 0.0f, 0.0f, 0.0f, 1.0f }
		};
	}

	mat4 getRotationMatrix() const
	{
		return rotation.getRotationMatrix();
	}

	mat4 getScaleMatrix() const
	{
		return {
			{ scale.getX(), 0.0f,         0.0f,         0.0f },
			{ 0.0f,         scale.getY(), 0.0f,         0.0f },
			{ 0.0f,         0.0f,         scale.getZ(), 0.0f },
			{ 0.0f,         0.0f,         0.0f,         1.0f }
		};
	}
};