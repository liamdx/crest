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
	forward = glm::vec3(0.0, 0.0, -1.0);
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
	position = position - lastPosition;
	updateModelPosition(position);	
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

	eulerAngles = eulerAngles - lastEuler;

	clampEulerAngles(eulerAngles);
	updateDirectionVectors();
	updateModelAngles(eulerAngles);
}

void TransformComponent::clampEulerAngles(glm::vec3& v)
{
	clampRotation(v.x);
	clampRotation(v.y);
	clampRotation(v.z);
}

void TransformComponent::clampRotation(float& value)
{
	if(value >= 180.0f)
	{
		value = -180.0f;
	}
	else if(value <= -180.0f)
	{
		value = 180.0f;
	}

}

void TransformComponent::updateModelAngles(glm::vec3 rotationChange)
{
	model = glm::rotate(model, glm::radians(glm::length(rotationChange)), glm::normalize(rotationChange));
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

	scale = scale - lastScale;
	updateModelScale(scale);
}

void TransformComponent::updateModelScale(glm::vec3 scaleChange)
{
	model = glm::scale(model, scaleChange);
}


void TransformComponent::updateDirectionVectors()
{
	glm::vec3 front = glm::vec3(0.0);
	front.x = glm::cos(glm::radians(eulerAngles.y)) * glm::cos(glm::radians(eulerAngles.x));
	front.y = glm::sin(glm::radians(eulerAngles.x));
	front.z = glm::sin(glm::radians(eulerAngles.y)) * glm::cos(glm::radians(eulerAngles.x));
	
	forward = glm::normalize(front);
	right = glm::normalize(glm::cross(front, worldUp)); // forward should be world up
	up = glm::normalize(glm::cross(right, forward));
}
