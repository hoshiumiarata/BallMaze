#pragma once

#include <vector>
#include "math/vector.h"

class Mesh
{
public:
	void setVertices(const std::vector<vec3>& vertices);
	void setNormals(const std::vector<vec3>& normals);
	void setIndices(const std::vector<unsigned int>& indices);
	void setTexCoords(const std::vector<vec2>& texCoords);

	const std::vector<vec3>& getVertices() const;
	const std::vector<vec3>& getNormals() const;
	const std::vector<unsigned int>& getIndices() const;
	const std::vector<vec2>& getTexCoords() const;
private:
	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<unsigned int> indices;
	std::vector<vec2> texCoords;
};