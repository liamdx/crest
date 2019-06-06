#include "TransformComponent.h"
#include "Common.h"

TransformComponent::TransformComponent()
{
	name = "TransformComponent";
	parent = nullptr;
	position = glm::vec3(0.0); eulerAngles = glm::vec3(0.01); scale = glm::vec3(1.0);
	localPosition = glm::vec3(0.0); localEulerAngles = glm::vec3(0.0); localScale = glm::vec3(1.0);
	forward = glm::vec3(0.0, 0.0, -1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	up = glm::vec3(0.0, 1.0, 0.0);
	worldUp = up;
	worldRight = right;
	worldForward = forward;
	model = glm::mat4(1.0);
	physicsOverride = false;
	update(0.0);
	updateModelMatrix();
}

TransformComponent::TransformComponent(std::shared_ptr<TransformComponent> _parent)
{
	name = "TransformComponent";
	parent = _parent;
	localPosition = glm::vec3(0.0); localEulerAngles = glm::vec3(0.01); localScale = glm::vec3(1.0);
	position = parent->position + localPosition; eulerAngles = parent->eulerAngles + localEulerAngles; scale = parent->scale + localScale;
	forward = glm::vec3(0.0, 0.0, -1.0);
	right = glm::vec3(1.0, 0.0, 0.0);
	up = glm::vec3(0.0, 1.0, 0.0);
	worldUp = up;
	worldRight = right;
	worldForward = forward;
	model = glm::mat4(1.0);
	physicsOverride = false;
	update(0.0);
	updateModelMatrix();
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
	update(0.0f);
	updateModelMatrix();
}

void TransformComponent::setPositionAbsolute(glm::vec3 newPosition)
{
	position = newPosition;
	updateModelMatrix();
}


void TransformComponent::addPosition(glm::vec3 newPosition)
{
	localPosition = localPosition + newPosition;
	if (parent == nullptr)
	{
		position = localPosition;
	}
	else
	{
		position = parent->position + localPosition;
	}
	update(0.0f);
	updateModelMatrix();
}

void TransformComponent::setEulerAngles(glm::vec3 newEulerAngles)
{
	//glm::vec3 lastEuler = eulerAngles;

	localEulerAngles = newEulerAngles;
	if (parent == nullptr)
	{
		eulerAngles = localEulerAngles;
	}
	else
	{
		eulerAngles = parent->eulerAngles + localEulerAngles;
	}

	// eulerAngles = eulerAngles - lastEuler;

	clampEulerAngles(eulerAngles);
	updateDirectionVectors();
	update(0.0f);
	updateModelMatrix();
}

void TransformComponent::setEulerAnglesAbsolute(glm::vec3 newRotation)
{
	eulerAngles = newRotation;
	update(0.0f);
	updateModelMatrix();
}


void TransformComponent::addEulerAngles(glm::vec3 newRotation)
{
	localEulerAngles = localEulerAngles + newRotation;
	if (parent == nullptr)
	{
		eulerAngles = localEulerAngles;
	}
	else
	{
		eulerAngles = parent->eulerAngles + localEulerAngles;
	}

	clampEulerAngles(eulerAngles);
	updateDirectionVectors();
	update(0.0f);
	updateModelMatrix();
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
		value -= -360.0f;
	}
	else if(value <= -180.0f)
	{
		value += 360.0f;
	}

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
	update(0.0f);
	updateModelMatrix();
}

void TransformComponent::setScaleAbsolute(glm::vec3 newScale)
{
	scale = newScale;
	updateModelMatrix();
}


void TransformComponent::addScale(glm::vec3 newScale)
{
	localScale = localScale + newScale;
	if (parent == nullptr)
	{
		scale = localScale;
	}
	else
	{
		scale = parent->scale + localScale;
	}
	update(0.0f);
	updateModelMatrix();
}

void TransformComponent::updateModelMatrix()
{
	model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(glm::length(eulerAngles)), glm::normalize(eulerAngles));
	model = glm::scale(model, scale);
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

void TransformComponent::update(float deltaTime)
{
	if (!physicsOverride)
	{
		if (parent == nullptr)
		{
			position = localPosition;
		}
		else
		{
			position = parent->position + localPosition;
		}


		if (parent == nullptr)
		{
			eulerAngles = localEulerAngles;
		}
		else
		{
			eulerAngles = parent->eulerAngles + localEulerAngles;
		}


		if (parent == nullptr)
		{
			scale = localScale;
		}
		else
		{
			scale = parent->scale + localScale;
		}
		updateModelMatrix();
	}
		
	
}
