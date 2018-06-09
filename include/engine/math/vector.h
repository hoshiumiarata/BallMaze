#pragma once

#include <initializer_list>
#include <cassert>
#include <cmath>

template <typename T, size_t size>
class Vector
{
public:
	Vector()
	{
		for (size_t i = 0; i < size; i++)
			data[i] = T();
	}

	Vector(std::initializer_list<T> list)
	{
		assert(list.size() <= size);

		size_t i = 0;
		for (const auto& element : list)
			data[i++] = element;

		for (; i < size; i++)
			data[i] = T();
	}

	const T& getX() const
	{
		return data[0];
	}
	void setX(const T& x)
	{
		data[0] = x;
	}
	const T& getY() const
	{
		return data[1];
	}
	void setY(const T& y)
	{
		data[1] = y;
	}
	const T& getZ() const
	{
		return data[2];
	}
	void setZ(const T& z)
	{
		data[2] = z;
	}
	const T& getW() const
	{
		return data[3];
	}
	void setW(const T& w)
	{
		data[3] = w;
	}

	const T& get(size_t index) const
	{
		assert(index < size);
		return data[index];
	}

	void set(size_t index, const T& value)
	{
		assert(index < size);
		data[index] = value;
	}

	T length() const
	{
		T len = T();
		for (size_t i = 0; i < size; i++)
			len += get(i) * get(i);
		return sqrt(len);
	}

	T sum() const
	{
		T sum = T();
		for (size_t i = 0; i < size; i++)
			sum += get(i);
		return sum;
	}

	T average() const
	{
		return sum() / size;
	}

	void normalize()
	{
		auto len = length();
		if (len == T())
			return;
		for (size_t i = 0; i < size; i++)
			set(i, get(i) / len);
	}

	Vector<T, size> normalized() const
	{
		Vector<T, size> result = *this;
		result.normalize();
		return result;
	}

	T distanceTo(const Vector<T, size>& rhs) const
	{
		return (rhs - *this).length();
	}

	T dot(const Vector<T, size>& rhs) const
	{
		T result = T();

		for (size_t i = 0; i < size; i++)
			result += get(i) * rhs.get(i);

		return result;
	}

	Vector<T, size> cross(const Vector<T, size>& rhs) const
	{
		assert(size == 3);
		return { getY() * rhs.getZ() - getZ() * rhs.getY(), getZ() * rhs.getX() - getX() * rhs.getZ(), getX() * rhs.getY() - getY() * rhs.getX() };
	}

	Vector<T, size> operator+(const Vector<T, size>& rhs) const
	{
		Vector<T, size> result;
		for (size_t i = 0; i < size; i++)
			result.set(i, get(i) + rhs.get(i));
		return result;
	}

	Vector<T, size> operator-(const Vector<T, size>& rhs) const
	{
		Vector<T, size> result;
		for (size_t i = 0; i < size; i++)
			result.set(i, get(i) - rhs.get(i));
		return result;
	}

	Vector<T, size> operator*(const T& rhs) const
	{
		Vector<T, size> result;
		for (size_t i = 0; i < size; i++)
			result.set(i, get(i) * rhs);
		return result;
	}

	Vector<T, size> operator/(const T& rhs) const
	{
		Vector<T, size> result;
		for (size_t i = 0; i < size; i++)
			result.set(i, get(i) / rhs);
		return result;
	}

	static Vector<T, size> lerp(const Vector<T, size>& a, const Vector<T, size>& b, T t)
	{
		return a + (b - a) * t;
	}

	operator const T*() const
	{
		return data;
	}
private:
	T data[size];
};

using vec1 = Vector<float, 1>;
using vec2 = Vector<float, 2>;
using vec3 = Vector<float, 3>;
using vec4 = Vector<float, 4>;