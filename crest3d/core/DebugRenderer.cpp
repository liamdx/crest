#include "DebugRenderer.h"


DebugRenderer::DebugRenderer() : shader("res/shaders/unassigned.vert", "res/shaders/unassigned.frag")
{
	
}


void DebugRenderer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color) 
{
	// Vertex data
	GLfloat points[12];

	points[0] = from.x();
	points[1] = from.y();
	points[2] = from.z();
	points[3] = color.x();
	points[4] = color.y();
	points[5] = color.z();

	points[6] = to.x();
	points[7] = to.y();
	points[8] = to.z();
	points[9] = color.x();
	points[10] = color.y();
	points[11] = color.z();
	shader.use();
	// delete what was in the buffer before
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	// fill it with new line data
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), &points, GL_STATIC_DRAW);
	//layout of the VBO
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

	// do the draw

	shader.setMat4("view", view);
	shader.setMat4("projection", projection);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}


void DebugRenderer::draw3dText(const btVector3& location, const char* textString)
{
	
}
void DebugRenderer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
	
}

int DebugRenderer::getDebugMode() const
{
	return 3;
}
void DebugRenderer::setDebugMode(int p)
{
	m = p;
}

void DebugRenderer::reportErrorWarning(const char* warningString)
{
	std::cout << "DebugRenderer: " << warningString << std::endl;
}


void DebugRenderer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar)
{
	
}
