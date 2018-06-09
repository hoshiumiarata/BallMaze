#include "engine/subsystems/graphics/opengl/glsl_shader_program.h"

#include <cassert>
#include <exception>

GLSLShaderProgram::~GLSLShaderProgram()
{
	if (program)
		glDeleteProgram(program);
}

void GLSLShaderProgram::addShader(ShaderType type, const std::string& text)
{
	GLuint shader;

	switch (type)
	{
	case ShaderType::Vertex:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case ShaderType::Fragment:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;
	default:
		throw std::runtime_error("GLSL Shader Program: Unsupported shader type");
	}

	auto source = text.c_str();
	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	shaders.push_back(shader);

	GLint isCompiled = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

		for (const auto& shader : shaders)
			glDeleteShader(shader);

		throw std::runtime_error("GLSL Shader Compiler: " + std::string(infoLog.begin(), infoLog.end()));
	}
}

void GLSLShaderProgram::link(std::initializer_list<std::pair<std::string, GLuint>> attributes)
{
	if (program)
	{
		uniforms.clear();
		glDeleteProgram(program);
	}

	program = glCreateProgram();

	for (const auto& shader : shaders)
		glAttachShader(program, shader);

	for (auto& attribute : attributes)
	{
		glBindAttribLocation(program, attribute.second, attribute.first.c_str());
	}

	glLinkProgram(program);

	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(program);
		for (const auto& shader : shaders)
			glDeleteShader(shader);

		throw std::runtime_error("GLSL Shader Linker: " + std::string(infoLog.begin(), infoLog.end()));
	}

	for (const auto& shader : shaders)
		glDetachShader(program, shader);

	shaders.clear();
}

void GLSLShaderProgram::enable()
{
	assert(program);
	glUseProgram(program);
}

void GLSLShaderProgram::disable()
{
	glUseProgram(0);
}

GLint GLSLShaderProgram::getUniformLocation(const std::string& name) const
{
	assert(program);
	auto cachedUniform = uniforms.find(name);
	if (cachedUniform != uniforms.end())
		return cachedUniform->second;

	GLint location = glGetUniformLocation(program, name.c_str());
	if (location < 0)
		throw std::runtime_error("GLSL: unknown uniform \"" + name + "\"");

	uniforms.emplace(name, location);

	return location;
}

void GLSLShaderProgram::setUniform(const std::string & name, int i)
{
	glUniform1i(getUniformLocation(name), i);
}

void GLSLShaderProgram::setUniform(const std::string& name, float v)
{
	glUniform1f(getUniformLocation(name), v);
}

void GLSLShaderProgram::setUniform(const std::string& name, const vec2& v)
{
	glUniform2fv(getUniformLocation(name), 1, v);
}

void GLSLShaderProgram::setUniform(const std::string& name, const vec3& v)
{
	glUniform3fv(getUniformLocation(name), 1, v);
}

void GLSLShaderProgram::setUniform(const std::string& name, const vec4& v)
{
	glUniform4fv(getUniformLocation(name), 1, v);
}

void GLSLShaderProgram::setUniform(const std::string& name, const mat3& v)
{
	glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, v);
}

void GLSLShaderProgram::setUniform(const std::string& name, const mat4& v)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, v);
}
