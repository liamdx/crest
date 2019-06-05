#pragma once
#include "Common.h"
#include "gfx/Shader.h"

class DebugRenderer : public btIDebugDraw
{
public:
	DebugRenderer(void);
	virtual ~DebugRenderer(void);

	struct _LINE {
		glm::vec3 from;
		glm::vec3 to;

		_LINE(glm::vec3 f, glm::vec3 t) {
			from = f;
			to = t;
		}
	};

	std::vector<_LINE> LINES;

	struct _COLOR {
		glm::vec3 col;

		_COLOR(glm::vec3 c) {
			col = c;
		}
	};

	std::vector<_COLOR> COLORS;

	GLuint vao, vbo[2];

	virtual void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) ;
	void draw3dText(const btVector3& location, const char* textString) override;
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
	virtual void setDebugMode(int debugMode);
	virtual int getDebugMode() const;
	void drawTriangle(const btVector3& v0, const btVector3& v1, const btVector3& v2, const btVector3& color, btScalar) override;

	void reportErrorWarning(const char* warningString) override;
	void bindBuffers();
	void doDraw();

	private:
	GLuint VBO, VAO;
	glm::mat4 model, view, projection;
	int _debugMode;
};
