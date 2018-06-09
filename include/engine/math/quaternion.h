#pragma once

#include "vector.h"
#include "matrix.h"

class Quaternion : public vec4
{
public:
	Quaternion()
		: vec4{ 0.0f, 0.0f, 0.0f, 1.0f }
	{

	}

	Quaternion(float x, float y, float z, float w)
		: vec4{ x, y, z, w }
	{

	}

	Quaternion(const vec3& axis, float angle)
		: vec4{ axis.getX() * std::sin(angle / 2.0f), axis.getY() * std::sin(angle / 2.0f), axis.getZ() * std::sin(angle / 2.0f), std::cos(angle / 2.0f) }
	{
	}

	Quaternion(const mat4& rotationMatrix)
	{
		const float t = rotationMatrix.get(0, 0) + rotationMatrix.get(1, 1) + rotationMatrix.get(2, 2);
		if (t > 0.0f)
		{
			const float r = std::sqrt(1 + t);
			const float s = 1.0f / (2.0f * r);
			setW(1.0f / 2.0f * r);
			setX((rotationMatrix.get(2, 1) - rotationMatrix.get(1, 2)) * s);
			setY((rotationMatrix.get(0, 2) - rotationMatrix.get(2, 0)) * s);
			setZ((rotationMatrix.get(1, 0) - rotationMatrix.get(0, 1)) * s);
		}
		else if (rotationMatrix.get(0, 0) > rotationMatrix.get(1, 1) && rotationMatrix.get(0, 0) > rotationMatrix.get(2, 2))
		{
			const float r = std::sqrt(1 + rotationMatrix.get(0, 0) - rotationMatrix.get(1, 1) - rotationMatrix.get(2, 2));
			const float s = 1.0f / (2.0f * r);
			setW((rotationMatrix.get(2, 1) - rotationMatrix.get(1, 2)) * s);
			setX(1.0f / 2.0f * r);
			setY((rotationMatrix.get(0, 1) + rotationMatrix.get(1, 0)) * s);
			setZ((rotationMatrix.get(2, 0) + rotationMatrix.get(0, 2)) * s);
		}
		else if (rotationMatrix.get(1, 1) > rotationMatrix.get(0, 0) && rotationMatrix.get(1, 1) > rotationMatrix.get(2, 2))
		{
			const float r = std::sqrt(1 - rotationMatrix.get(0, 0) + rotationMatrix.get(1, 1) - rotationMatrix.get(2, 2));
			const float s = 1.0f / (2.0f * r);
			setW((rotationMatrix.get(0, 2) - rotationMatrix.get(2, 0)) * s);
			setX((rotationMatrix.get(0, 1) + rotationMatrix.get(1, 0)) * s);
			setY(1.0f / 2.0f * r);
			setZ((rotationMatrix.get(2, 1) + rotationMatrix.get(1, 2)) * s);
		}
		else
		{
			const float r = std::sqrt(1 - rotationMatrix.get(0, 0) - rotationMatrix.get(1, 1) + rotationMatrix.get(2, 2));
			const float s = 1.0f / (2.0f * r);
			setW((rotationMatrix.get(1, 0) - rotationMatrix.get(0, 1)) * s);
			setX((rotationMatrix.get(0, 2) + rotationMatrix.get(2, 0)) * s);
			setY((rotationMatrix.get(2, 1) + rotationMatrix.get(1, 2)) * s);
			setZ(1.0f / 2.0f * r);
		}
	}

	vec3 rotate(const vec3& vector) const
	{
		Quaternion result = *this * vector * this->conjugate();

		return { result.getX(), result.getY(), result.getZ() };
	}

	Quaternion conjugate() const
	{
		return Quaternion(-getX(), -getY(), -getZ(), getW());
	}

	Quaternion operator*(const Quaternion& rhs) const
	{
		return Quaternion(
			getW() * rhs.getX() + getX() * rhs.getW() + getY() * rhs.getZ() - getZ() * rhs.getY(),
			getW() * rhs.getY() - getX() * rhs.getZ() + getY() * rhs.getW() + getZ() * rhs.getX(),
			getW() * rhs.getZ() + getX() * rhs.getY() - getY() * rhs.getX() + getZ() * rhs.getW(),
			getW() * rhs.getW() - getX() * rhs.getX() - getY() * rhs.getY() - getZ() * rhs.getZ()
		);
	}

	Quaternion operator*(const vec3& rhs) const
	{
		return *this * Quaternion(rhs.getX(), rhs.getY(), rhs.getZ(), 1.0f);
	}

	mat4 getRotationMatrix() const
	{
		const float x = getX();
		const float y = getY();
		const float z = getZ();
		const float w = getW();

		return {
			{ 1 - 2 * (y * y + z * z), 2 * (x * y - z * w)    , 2 * (x * z + y * w)    , 0.0f },
			{ 2 * (x * y + z * w)    , 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)    , 0.0f },
			{ 2 * (x * z - y * w)    , 2 * (y * z + x * w)    , 1 - 2 * (x * x + y * y), 0.0f },
			{ 0.0f                   , 0.0f,                    0.0f,                    1.0f }
		};
	}
};