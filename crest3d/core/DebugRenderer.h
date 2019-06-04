#pragma once
#include "Common.h"
#include "gfx/Shader.h"

class DebugRenderer : public btIDebugDraw
{
public:
	DebugRenderer();

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void draw3dText(const btVector3& location, const char* textString) override;
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
	void setDebugMode(int p) override;
	int getDebugMode() const override;
	void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar) override;

	void reportErrorWarning(const char* warningString) override;

	void setView(glm::mat4 newView) { view = newView; }
	void setProjection(glm::mat4 newProjection) { projection = newProjection; }

private:
	GLuint VBO, VAO;
	glm::mat4 view, projection;
	Shader shader;
	int _debugMode;
	int m;
};
