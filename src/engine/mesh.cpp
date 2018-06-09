#include "engine/mesh.h"

void Mesh::setVertices(const std::vector<vec3>& vertices)
{
	this->vertices = vertices;
}

void Mesh::setNormals(const std::vector<vec3>& normals)
{
	this->normals = normals;
}

void Mesh::setIndices(const std::vector<unsigned int>& indices)
{
	this->indices = indices;
}

void Mesh::setTexCoords(const std::vector<vec2>& texCoords)
{
	this->texCoords = texCoords;
}

const std::vector<vec3>& Mesh::getVertices() const
{
	return vertices;
}

const std::vector<vec3>& Mesh::getNormals() const
{
	return normals;
}

const std::vector<unsigned int>& Mesh::getIndices() const
{
	return indices;
}

const std::vector<vec2>& Mesh::getTexCoords() const
{
	return texCoords;
}
