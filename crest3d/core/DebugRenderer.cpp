#include "DebugRenderer.h"

DebugRenderer::DebugRenderer()
{
}

DebugRenderer::~DebugRenderer()
{
}

void DebugRenderer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	LINES.push_back(_LINE(glm::vec3(from.getX(), from.getY(), from.getZ()), glm::vec3(to.getX(), to.getY(), to.getZ())));
	COLORS.push_back(_COLOR(glm::vec3(color.getX(), color.getY(), color.getZ())));
}

void DebugRenderer::bindBuffers()
{
	// Memory leak somewhere in here
	if (LINES.size() > 0)
	{
		glDeleteBuffers(2, vbo);
		glDeleteVertexArrays(1, &vao);

		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);

		glGenBuffers(2, vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, LINES.size() * sizeof(_LINE), &LINES[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, COLORS.size() * sizeof(_COLOR), &COLORS[0], GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void DebugRenderer::doDraw()
{
	//glClear(GL_DEPTH_BUFFER_BIT);
	glEnable(GL_LINE_SMOOTH);
	glLineWidth(2.0);
	glBindVertexArray(vao);
	glDrawArrays(GL_LINES, 0, LINES.size() * 2);
	LINES.clear();
	COLORS.clear();
}

void DebugRenderer::draw3dText(const btVector3& location, const char* textString)
{
}
void DebugRenderer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
}

int DebugRenderer::getDebugMode() const
{
	return 1;
}

void DebugRenderer::setDebugMode(int debugMode)
{
	_debugMode = debugMode;
}

void DebugRenderer::reportErrorWarning(const char* warningString)
{
	std::cout << "DebugRenderer: " << warningString << std::endl;
}

void DebugRenderer::drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar)
{
}