#include "TransformComponent.h"
#include "Common.h"

TransformComponent::TransformComponent()
{
	name = "TransformComponent";
	position, eulerAngles, scale = glm::vec3(0.0);
	localPosition, localEulerAngles, localScale = glm::vec3(0.0);
	forward = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	up = glm::vec3(0.0, 1.0, 0.0);
	worldUp = up;
	worldRight = right;
	worldForward = forward;
}

TransformComponent::TransformComponent(std::shared_ptr<TransformComponent> _parent)
{
	name = "TransformComponent";
	parent = _parent;
	position, eulerAngles, scale = glm::vec3(0.0);
	localPosition, localEulerAngles, localScale = glm::vec3(0.0);
	forward = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	up = glm::vec3(0.0, 1.0, 0.0);
	worldUp = up;
	worldRight = right;
	worldForward = forward;
}


void TransformComponent::setPosition(glm::vec3 newPosition)
{
	localPosition = newPosition;
	if (parent == nullptr)
	{
		position = localPosition;
	}
	else
	{
		position = parent->position + localPosition;
	}
	
}

void TransformComponent::setEulerAngles(glm::vec3 newEulerAngles)
{
	localEulerAngles = newEulerAngles;
	if (parent == nullptr)
	{
		eulerAngles = localEulerAngles;
	}
	else
	{
		eulerAngles = parent->eulerAngles + localEulerAngles;
	}
	updateDirectionVectors();
}

void TransformComponent::setScale(glm::vec3 newScale)
{
	localScale = newScale;
	if (parent == nullptr)
	{
		scale = localScale;
	}
	else
	{
		scale = parent->scale + localScale;
	}
}

void TransformComponent::updateDirectionVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(eulerAngles.z)) * cos(glm::radians(eulerAngles.y));
	front.y = sin(glm::radians(eulerAngles.y));
	front.z = sin(glm::radians(eulerAngles.z)) * cos(glm::radians(eulerAngles.z));
	
	forward = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp)); // forward should be world up
	up = glm::normalize(glm::cross(right, forward));
}
