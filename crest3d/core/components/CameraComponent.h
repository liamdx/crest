#pragma once

#include "EngineComponent.h"

class CameraComponent : public EngineComponent
{
public:
	CameraComponent(std::shared_ptr<Entity> e);
	~CameraComponent() override {};

	glm::mat4 GetViewProjectionMatrix();

	inline glm::mat4 GetProjectionMatrix() { return projection; }
	glm::mat4 GetViewMatrix();
	void updateProjection(float _fov, float _width, float _height);

	// culling checks
	bool checkSphere(glm::vec3 position, float radius);
	bool checkPoint(glm::vec3 position);

	void MakeFrustum();
	float fov;
private:
	float width, height;
	float nearPlane, farPlane;
	glm::mat4 projection;
	std::vector<glm::vec4> frustumPlanes;

	glm::vec4 normalizePlane(glm::vec4 plane);
	float planeDotCoord(glm::vec4 a, glm::vec3 b);
};