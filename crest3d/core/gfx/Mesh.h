#pragma once

#include "Common.h"
#include "Shader.h"

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 TexCoords;
	glm::vec3 tangent;
};

struct Face
{
	std::vector<int> indices;
	int numIndices;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::vector<Face> faces;
	std::vector<float> physicsPoints;
	std::vector<int> physicsIndices;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		//calcMeshBounds();
		setupMesh();
		physicsPoints = getVertexValues();
		physicsIndices = getIndexValues();
	};

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, std::vector<Face> faces)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		this->faces = faces;

		//calcMeshBounds();
		setupMesh();
	};
	void Draw(Shader shader);
	void TestDraw(Shader shader);
	void calcMeshBounds();
	//physics position;

	unsigned int vao, vbo, ibo;
	void setupMesh();
    float getCullSphereRadius();
	float xBound, yBound, zBound;

	std::vector<glm::vec3> getVertexPositions();
	std::vector<float> getVertexValues();
	std::vector<int> getIndexValues();

	const int numVertices() { return vertices.size(); }
	const int numIndices() { return indices.size(); }


};