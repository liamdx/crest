#include "TransformComponent.h"
#include "Common.h"

TransformComponent::TransformComponent()
{
	name = "TransformComponent";
	parent = nullptr;
	position = glm::vec3(1.0); eulerAngles = glm::vec3(1.0); scale = glm::vec3(1.0);
	localPosition = glm::vec3(1.0); localEulerAngles = glm::vec3(1.0); localScale = glm::vec3(1.0);
	forward = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	up = glm::vec3(0.0, 1.0, 0.0);
	worldUp = up;
	worldRight = right;
	worldForward = forward;
	model = glm::mat4(1.0);
}

TransformComponent::TransformComponent(std::shared_ptr<TransformComponent> _parent)
{
	name = "TransformComponent";
	parent = _parent;
	position = glm::vec3(1.0); eulerAngles = glm::vec3(0.0); scale = glm::vec3(1.0);
	localPosition = glm::vec3(1.0); localEulerAngles = glm::vec3(0.0); localScale = glm::vec3(1.0);
	forward = glm::vec3(0.0, 0.0, 1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	up = glm::vec3(0.0, 1.0, 0.0);
	worldUp = up;
	worldRight = right;
	worldForward = forward;
	model = glm::mat4(1.0);
}


void TransformComponent::setPosition(glm::vec3 newPosition)
{
	glm::vec3 lastPosition = position;

	localPosition = newPosition;
	if (parent == nullptr)
	{
		position = localPosition;
	}
	else
	{
		position = parent->position + localPosition;
	}

	updateModelPosition(position - lastPosition);
	
}

void TransformComponent::updateModelPosition(glm::vec3 positionChange)
{
	model = glm::translate(model, positionChange);
}


void TransformComponent::setEulerAngles(glm::vec3 newEulerAngles)
{
	glm::vec3 lastEuler = eulerAngles;

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
	updateModelAngles(eulerAngles - lastEuler);
}

void TransformComponent::updateModelAngles(glm::vec3 rotationChange)
{
	model = glm::rotate(model, rotationChange.x, glm::vec3(1.0, 0.0, 0.0));
	model = glm::rotate(model, rotationChange.y, glm::vec3(0.0, 1.0, 0.0));
	model = glm::rotate(model, rotationChange.z, glm::vec3(0.0, 0.0, 1.0));
}


void TransformComponent::setScale(glm::vec3 newScale)
{
	glm::vec3 lastScale = scale;
	localScale = newScale;
	if (parent == nullptr)
	{
		scale = localScale;
	}
	else
	{
		scale = parent->scale + localScale;
	}
	updateModelScale(scale - lastScale);
}

void TransformComponent::updateModelScale(glm::vec3 scaleChange)
{
	model = glm::scale(model, scaleChange);
}


void TransformComponent::updateDirectionVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(eulerAngles.x)) * cos(glm::radians(eulerAngles.y));
	front.y = sin(glm::radians(eulerAngles.y));
	front.z = sin(glm::radians(eulerAngles.x)) * cos(glm::radians(eulerAngles.x));
	
	forward = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp)); // forward should be world up
	up = glm::normalize(glm::cross(right, forward));
}
