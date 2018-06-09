#pragma once

#include <vector>

class IndexBuffer
{
public:
	virtual ~IndexBuffer() {};

	virtual void bind() = 0;
	virtual void setData(const std::vector<unsigned int>& data) = 0;
};