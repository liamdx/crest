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

void Mesh::Draw(Shader shader)
{
	int diffuseCount = 0;
	int specularCount = 0;
	int reflectionCount = 0;
	int normalCount = 0;


	for (unsigned int i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		if (textures[i].t_Type == "diffuse")
		{
			shader.setInt("mat.m_Diffuse", i);
			diffuseCount += 1;
			glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
		}
		else if (textures[i].t_Type == "specular")
		{
			shader.setInt("mat.m_Specular", i);
			specularCount += 1;
			glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
		}
		else if (textures[i].t_Type == "reflection")
		{
			shader.setInt("mat.m_Reflection", i);
			reflectionCount += 1;
			glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
		}

		else if (textures[i].t_Type == "normal")
		{
			shader.setInt("mat.m_Normal", i);
			normalCount += 1;
			glBindTexture(GL_TEXTURE_2D, textures[i].t_Id);
		}
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


void Mesh::calcMeshBounds()
{
	float currentMaxX = 0.0f;
	float currentMaxY = 0.0f;
	float currentMaxZ = 0.0f;

	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		if (vertices[i].position.GetX() > currentMaxX)
		{
			currentMaxX = vertices[i].position.GetX();
		}

		if (vertices[i].position.GetY() > currentMaxY)
		{
			currentMaxY = vertices[i].position.GetY();
		}

		if (vertices[i].position.GetZ() > currentMaxZ)
		{
			currentMaxZ = vertices[i].position.GetZ();
		}
	}

	xBound = currentMaxX;
	yBound = currentMaxY;
	zBound = currentMaxZ;
}
