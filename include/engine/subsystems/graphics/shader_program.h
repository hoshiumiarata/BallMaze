#pragma once

#include <string>

class ShaderProgram
{
public:
	virtual ~ShaderProgram();

	enum class ShaderType {
		Vertex,
		Fragment
	};

	virtual void addShader(ShaderType type, const std::string& text) = 0;

	virtual void enable() = 0;
	virtual void disable() = 0;
};