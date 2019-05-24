
#pragma once

#include "EngineComponent.h"

class CameraComponent : public EngineComponent
{
public:
	CameraComponent(std::shared_ptr<Entity> e) { attachedEntity = e; name = "CameraComponent"; };
	~CameraComponent() override {};

	void init() override;

	glm::mat4 GetViewProjectionMatrix();

	inline glm::mat4 GetProjectionMatrix() { return projection; }
	glm::mat4 GetViewMatrix();
	void updateProjection(float _fov, float _width, float _height);

private:
	float fov;
	float width, height;
	float nearPlane, farPlane;
	glm::mat4 projection;
};