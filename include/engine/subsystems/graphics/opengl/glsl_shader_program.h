#pragma once

#include <vector>
#include <unordered_map>
#include <initializer_list>

#include "../shader_program.h"
#include "engine/math/vector.h"
#include "engine/math/matrix.h"

#include <GL/glew.h>

class GLSLShaderProgram : public ShaderProgram
{
public:
	~GLSLShaderProgram();

	virtual void addShader(ShaderType type, const std::string& text) override;
	virtual void enable() override;
	virtual void disable() override;

	void link(std::initializer_list<std::pair<std::string, GLuint>> attributes);

	GLint getUniformLocation(const std::string& name) const;

	void setUniform(const std::string& name, int i);
	void setUniform(const std::string& name, float v);
	void setUniform(const std::string& name, const vec2& v);
	void setUniform(const std::string& name, const vec3& v);
	void setUniform(const std::string& name, const vec4& v);
	void setUniform(const std::string& name, const mat3& v);
	void setUniform(const std::string& name, const mat4& v);

private:
	GLuint program = 0;
	std::vector<GLuint> shaders;
	mutable std::unordered_map<std::string, GLint> uniforms;
};