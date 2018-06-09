#pragma once

#include <vector>
#include "engine/math/vector.h"

class VertexBuffer
{
public:
	virtual ~VertexBuffer() {};

	virtual void bind() = 0;
	virtual void setData(const std::vector<vec2>& data) = 0;
	virtual void setData(const std::vector<vec3>& data) = 0;
};