#pragma once

#include "Common.h"
#include "Material.h"

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
		generateConvexHull();
	};

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, std::vector<Face> faces)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;
		this->faces = faces;

		//calcMeshBounds();
		setupMesh();
		generateConvexHull();
	};

	Mesh(std::vector<float> vertexPositions, std::vector<unsigned int> indices);
	void Draw(Shader shader);
	void Draw(std::shared_ptr<Shader> shader);
	void Draw(Shader* shader);
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

	void generateConvexHull();

	const int numVertices() { return vertices.size(); }
	const int numIndices() { return indices.size(); }

	// convex hull stuff
	//quickhull::QuickHull<float> qh;
	//std::vector<quickhull::Vector3<float>> pointCloud;

	std::vector<float> hullVertexPositions;
	std::vector<unsigned int> hullIndices;
};