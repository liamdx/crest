#include "Mesh.h"

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	glBindVertexArray(0);
}
float Mesh::getCullSphereRadius()
{
	if ((xBound >= yBound) && (xBound >= zBound))
		return xBound;
	else if ((yBound >= xBound) && (yBound >= zBound))
		return yBound;
	else
		return zBound;
}

Mesh::Mesh(std::vector<float> vertexPositions, std::vector<unsigned> indices)
{
	this->indices = indices;
	std::vector<Vertex> newVerts;
	glm::vec3 currentPosition;
	Vertex v;
	int counter = 0;

	for (int i = 0; i < vertexPositions.size(); i++)
	{
		if (counter == 0)
		{
			currentPosition.x = vertexPositions.at(i);
			counter += 1;
		}
		if (counter == 1)
		{
			currentPosition.y = vertexPositions.at(i);
			counter += 1;
		}
		if (counter == 2)
		{
			currentPosition.z = vertexPositions.at(i);
			v.position = currentPosition;
			v.normal = glm::vec3(0.0);
			v.tangent = glm::vec3(0.0);
			v.TexCoords = glm::vec2(1.0);
			newVerts.emplace_back(v);
			counter = 0;
		}
	}
	this->vertices = newVerts;

	setupMesh();
}

void Mesh::Draw(Shader shader)
{
	int diffuseCount = 0;
	int specularCount = 0;
	int reflectionCount = 0;
	int normalCount = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		unsigned int uniformLocation = shader.textureIdMappings[textures[i].t_Type];
		shader.setIntID(uniformLocation, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
	}

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindVertexArray(0);
}

void Mesh::Draw(std::shared_ptr<Shader> shader)
{
	int diffuseCount = 0;
	int specularCount = 0;
	int reflectionCount = 0;
	int normalCount = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		unsigned int uniformLocation = shader->textureIdMappings[textures[i].t_Type];
		shader->setIntID(uniformLocation, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);

		/*if (textures[i].t_Type == TextureType::diffuse)
		{
			shader->setInt("mat.m_Diffuse", i);
			diffuseCount += 1;
			glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
		}
		else if (textures[i].t_Type == TextureType::specular)
		{
			shader->setInt("mat.m_Specular", i);
			specularCount += 1;
			glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
		}
		else if (textures[i].t_Type == TextureType::reflection)
		{
			shader->setInt("mat.m_Reflection", i);
			reflectionCount += 1;
			glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
		}

		else if (textures[i].t_Type == TextureType::normal)
		{
			shader->setInt("mat.m_Normal", i);
			normalCount += 1;
			glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
		}*/
	}

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindVertexArray(0);
}

void Mesh::Draw(Shader* shader)
{
	int diffuseCount = 0;
	int specularCount = 0;
	int reflectionCount = 0;
	int normalCount = 0;

	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		unsigned int uniformLocation = shader->textureIdMappings[textures[i].t_Type];
		shader->setIntID(uniformLocation, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
	}

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	for (int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	glBindVertexArray(0);
}

void Mesh::TestDraw(Shader shader)
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

std::vector<glm::vec3> Mesh::getVertexPositions()
{
	std::vector<glm::vec3> vertexPositions;
	for (int i = 0; i < vertices.size(); i++)
	{
		vertexPositions.emplace_back(vertices.at(i).position);
	}

	return(vertexPositions);
}

std::vector<float> Mesh::getVertexValues()
{
	std::vector<float> v;
	for (int i = 0; i < vertices.size(); i++)
	{
		auto currentVertex = vertices.at(i);
		v.emplace_back(currentVertex.position.x);
		v.emplace_back(currentVertex.position.y);
		v.emplace_back(currentVertex.position.z);
	}

	return(v);
}

std::vector<int> Mesh::getIndexValues()
{
	std::vector<int> iv;
	for (int i = 0; i < indices.size(); i++)
	{
		iv.emplace_back((int)indices.at(i));
	}
	return iv;
}

void Mesh::calcMeshBounds()
{
	float currentMaxX = 0.0f;
	float currentMaxY = 0.0f;
	float currentMaxZ = 0.0f;

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].position.x > currentMaxX)
		{
			currentMaxX = vertices[i].position.x;
		}

		if (vertices[i].position.y > currentMaxY)
		{
			currentMaxY = vertices[i].position.y;
		}

		if (vertices[i].position.z > currentMaxZ)
		{
			currentMaxZ = vertices[i].position.z;
		}
	}

	xBound = currentMaxX;
	yBound = currentMaxY;
	zBound = currentMaxZ;
}

void Mesh::generateConvexHull()
{
}