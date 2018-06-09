#pragma once

#include <type_traits>
#include <exception>
#include <stdexcept>
#include <initializer_list>
#include <cassert>

#include "vector.h"

template <typename T, size_t rows, size_t columns>
class Matrix
{
public:
	Matrix()
	{
		for (size_t i = 0; i < rows; i++)
			for (size_t j = 0; j < columns; j++)
				set(i, j, T());
	}

	Matrix(std::initializer_list<std::initializer_list<T>> elements)
	{
		set(elements);
	}

	template <typename rhs_T, size_t rhs_rows, size_t rhs_columns>
	Matrix(const Matrix<rhs_T, rhs_rows, rhs_columns>& rhs)
	{
		for (size_t i = 0; i < rows; i++)
			for (size_t j = 0; j < columns; j++)
				if (i < rhs_rows && j < rhs_columns)
					set(i, j, rhs.get(i, j));
				else
					set(i, j, T());
	}

	static Matrix<T, rows, columns> identity()
	{
		Matrix<T, rows, columns> result;
		for (size_t i = 0; i < rows; i++)
			for (size_t j = 0; j < columns; j++)
				result.set(i, j, i == j ? static_cast<T>(1) : T());
		return result;
	}

	Matrix<T, rows, columns> inversed() const
	{
		Matrix<T, rows, columns> result;
		T inv[rows * columns];
		T det;
		if (rows == 3 && columns == 3)
		{
			inv[0] = data[4] * data[8] - data[5] * data[7];
			inv[1] = data[7] * data[2] - data[1] * data[8];
			inv[2] = data[1] * data[5] - data[4] * data[2];
			inv[3] = data[6] * data[5] - data[3] * data[8];
			inv[4] = data[0] * data[8] - data[2] * data[6];
			inv[5] = data[2] * data[3] - data[0] * data[5];
			inv[6] = data[3] * data[7] - data[4] * data[6];
			inv[7] = data[6] * data[1] - data[0] * data[7];
			inv[8] = data[0] * data[4] - data[1] * data[3];

			det = data[0] * inv[0] + data[3] * inv[1] + data[6] * inv[2];
		}
		else if (rows == 4 && columns == 4)
		{
			inv[0] = data[5] * data[10] * data[15] -
				data[5] * data[11] * data[14] -
				data[9] * data[6] * data[15] +
				data[9] * data[7] * data[14] +
				data[13] * data[6] * data[11] -
				data[13] * data[7] * data[10];

			inv[4] = -data[4] * data[10] * data[15] +
				data[4] * data[11] * data[14] +
				data[8] * data[6] * data[15] -
				data[8] * data[7] * data[14] -
				data[12] * data[6] * data[11] +
				data[12] * data[7] * data[10];

			inv[8] = data[4] * data[9] * data[15] -
				data[4] * data[11] * data[13] -
				data[8] * data[5] * data[15] +
				data[8] * data[7] * data[13] +
				data[12] * data[5] * data[11] -
				data[12] * data[7] * data[9];

			inv[12] = -data[4] * data[9] * data[14] +
				data[4] * data[10] * data[13] +
				data[8] * data[5] * data[14] -
				data[8] * data[6] * data[13] -
				data[12] * data[5] * data[10] +
				data[12] * data[6] * data[9];

			inv[1] = -data[1] * data[10] * data[15] +
				data[1] * data[11] * data[14] +
				data[9] * data[2] * data[15] -
				data[9] * data[3] * data[14] -
				data[13] * data[2] * data[11] +
				data[13] * data[3] * data[10];

			inv[5] = data[0] * data[10] * data[15] -
				data[0] * data[11] * data[14] -
				data[8] * data[2] * data[15] +
				data[8] * data[3] * data[14] +
				data[12] * data[2] * data[11] -
				data[12] * data[3] * data[10];

			inv[9] = -data[0] * data[9] * data[15] +
				data[0] * data[11] * data[13] +
				data[8] * data[1] * data[15] -
				data[8] * data[3] * data[13] -
				data[12] * data[1] * data[11] +
				data[12] * data[3] * data[9];

			inv[13] = data[0] * data[9] * data[14] -
				data[0] * data[10] * data[13] -
				data[8] * data[1] * data[14] +
				data[8] * data[2] * data[13] +
				data[12] * data[1] * data[10] -
				data[12] * data[2] * data[9];

			inv[2] = data[1] * data[6] * data[15] -
				data[1] * data[7] * data[14] -
				data[5] * data[2] * data[15] +
				data[5] * data[3] * data[14] +
				data[13] * data[2] * data[7] -
				data[13] * data[3] * data[6];

			inv[6] = -data[0] * data[6] * data[15] +
				data[0] * data[7] * data[14] +
				data[4] * data[2] * data[15] -
				data[4] * data[3] * data[14] -
				data[12] * data[2] * data[7] +
				data[12] * data[3] * data[6];

			inv[10] = data[0] * data[5] * data[15] -
				data[0] * data[7] * data[13] -
				data[4] * data[1] * data[15] +
				data[4] * data[3] * data[13] +
				data[12] * data[1] * data[7] -
				data[12] * data[3] * data[5];

			inv[14] = -data[0] * data[5] * data[14] +
				data[0] * data[6] * data[13] +
				data[4] * data[1] * data[14] -
				data[4] * data[2] * data[13] -
				data[12] * data[1] * data[6] +
				data[12] * data[2] * data[5];

			inv[3] = -data[1] * data[6] * data[11] +
				data[1] * data[7] * data[10] +
				data[5] * data[2] * data[11] -
				data[5] * data[3] * data[10] -
				data[9] * data[2] * data[7] +
				data[9] * data[3] * data[6];

			inv[7] = data[0] * data[6] * data[11] -
				data[0] * data[7] * data[10] -
				data[4] * data[2] * data[11] +
				data[4] * data[3] * data[10] +
				data[8] * data[2] * data[7] -
				data[8] * data[3] * data[6];

			inv[11] = -data[0] * data[5] * data[11] +
				data[0] * data[7] * data[9] +
				data[4] * data[1] * data[11] -
				data[4] * data[3] * data[9] -
				data[8] * data[1] * data[7] +
				data[8] * data[3] * data[5];

			inv[15] = data[0] * data[5] * data[10] -
				data[0] * data[6] * data[9] -
				data[4] * data[1] * data[10] +
				data[4] * data[2] * data[9] +
				data[8] * data[1] * data[6] -
				data[8] * data[2] * data[5];

			det = data[0] * inv[0] + data[1] * inv[4] + data[2] * inv[8] + data[3] * inv[12];
		}
		else
		{
			throw std::invalid_argument("Unimplemented");
		}

		assert(det != T());

		for (size_t i = 0; i < columns * rows; i++)
			result.data[i] = inv[i] / det;

		return result;
	}

	Matrix<T, columns, rows> transposed() const
	{
		Matrix<T, columns, rows> result;

		for (size_t i = 0; i < rows; i++)
			for (size_t j = 0; j < columns; j++)
				result.set(j, i, get(i, j));

		return result;
	}

	const T& get(size_t row, size_t column) const
	{
		return data[index(row, column)];
	}

	void set(size_t row, size_t column, const T& element)
	{
		data[index(row, column)] = element;
	}

	void set(std::initializer_list<std::initializer_list<T>> elements)
	{
		assert(elements.size() <= rows);
		size_t i = 0;
		for (const auto& row : elements)
		{
			assert(row.size() <= columns);
			size_t j = 0;
			for (const auto& element : row)
				set(i, j++, element);
			i++;
		}
	}

	template <typename rhs_T, size_t rhs_rows, size_t rhs_columns>
	Matrix<T, rows, columns>& operator=(const Matrix<rhs_T, rhs_rows, rhs_columns>& rhs)
	{
		for (size_t i = 0; i < rows; i++)
			for (size_t j = 0; j < columns; j++)
				if (i < rhs_rows && j < rhs_columns)
					set(i, j, rhs.get(i, j));
	}

	template <size_t rhs_columns>
	Matrix<T, rows, rhs_columns> operator*(const Matrix<T, columns, rhs_columns>& rhs) const
	{
		Matrix<T, rows, rhs_columns> result;
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < rhs_columns; j++)
			{
				T cell = T();
				for (size_t k = 0; k < columns; k++)
					cell += get(i, k) * rhs.get(k, j);
				result.set(i, j, cell);
			}
		}
		return result;
	}

	Vector<T, rows> operator*(const Vector<T, columns>& rhs) const
	{
		Vector<T, rows> result;

		for (size_t i = 0; i < rows; i++)
		{
			T cell = T();
			for (size_t j = 0; j < columns; j++)
			{
				cell += get(i, j) * rhs.get(j);
			}
			result.set(i, cell);
		}

		return result;
	}

	operator const T*() const
	{
		return data;
	}
private:
	inline size_t index(size_t row, size_t column) const
	{
		return rows * column + row;
	}

	T data[rows * columns];
};

using mat3 = Matrix<float, 3, 3>;
using mat4 = Matrix<float, 4, 4>;