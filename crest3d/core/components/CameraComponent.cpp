#include "CameraComponent.h"
#include "Entity.h"
#include "Common.h"

void CameraComponent::init()
{
	nearPlane = 0.01;
	farPlane = 500;
	width = 1280;
	height = 720;
	fov = 70;
	updateProjection(fov, width, height);
}

glm::mat4 CameraComponent::GetViewProjectionMatrix()
{
	glm::mat4 view = glm::lookAt(attachedEntity->transform->position,
		attachedEntity->transform->position + attachedEntity->transform->forward,
		attachedEntity->transform->up);

	return projection * view;
}

glm::mat4 CameraComponent::GetViewMatrix()
{
	return glm::lookAt(attachedEntity->transform->position,
		attachedEntity->transform->position + attachedEntity->transform->forward,
		attachedEntity->transform->up);
}


void CameraComponent::updateProjection(float _fov, float _width, float _height)
{
	projection = glm::perspectiveFov(glm::radians(_fov), _width, _height, nearPlane, farPlane);
	fov = _fov;
	width = _width;
	height = _height;
}
