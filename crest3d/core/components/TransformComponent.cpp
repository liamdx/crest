#include "TransformComponent.h"
#include "Common.h"

TransformComponent::TransformComponent()
{
	name = "TransformComponent";
	parent = nullptr;
	position = glm::vec3(0.0); eulerAngles = glm::vec3(0.0); scale = glm::vec3(1.0);
	rotation = glm::quat(glm::radians(eulerAngles));
	localPosition = glm::vec3(0.0); localEulerAngles = glm::vec3(0.0); localScale = glm::vec3(1.0);
	localRotation = glm::quat(glm::radians(localEulerAngles));
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
	parent = _parent;
	name = "TransformComponent";
	position = glm::vec3(0.0); eulerAngles = glm::vec3(0.0); scale = glm::vec3(1.0);
	rotation = glm::quat(glm::radians(eulerAngles));
	localPosition = glm::vec3(0.0); localEulerAngles = glm::vec3(0.0); localScale = glm::vec3(1.0);
	localRotation = glm::quat(glm::radians(localEulerAngles));
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
}

void TransformComponent::setPositionAbsolute(glm::vec3 newPosition)
{
	position = newPosition;
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
	updateRotation();
	updateDirectionVectors();
	clampEulerAngles(eulerAngles);
}

void TransformComponent::setEulerAnglesAbsolute(glm::vec3 newRotation)
{
	eulerAngles = newRotation;
	updateRotation();
	updateDirectionVectors();
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
	updateRotation();
	updateDirectionVectors();
}

void TransformComponent::updateRotation()
{
	localRotation = glm::quat(glm::radians(localEulerAngles));
	rotation = glm::quat(glm::radians(eulerAngles));
}

void TransformComponent::updateEulerAngles()
{
	localEulerAngles = glm::eulerAngles(localRotation);
	eulerAngles = glm::eulerAngles(rotation);
}

void TransformComponent::clampEulerAngles(glm::vec3& v)
{
	clampRotation(v.x);
	clampRotation(v.y);
	clampRotation(v.z);
}

void TransformComponent::clampRotation(float& value)
{
	if (value >= 180.0f)
	{
		value -= -360.0f;
	}
	else if (value <= -180.0f)
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
		scale = glm::vec3(parent->scale.x * localScale.x, parent->scale.y * localScale.y, parent->scale.z * localScale.z);
	}
}

void TransformComponent::setScaleAbsolute(glm::vec3 newScale)
{
	scale = newScale;
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
		scale = glm::vec3(parent->scale.x * localScale.x, parent->scale.y * localScale.y, parent->scale.z * localScale.z);
	}
}

void TransformComponent::updateModelMatrix()
{
	localModelMatrix = glm::translate(glm::mat4(1.0), position);
	localModelMatrix = localModelMatrix * glm::mat4(rotation);
	localModelMatrix = glm::scale(localModelMatrix, scale);

	if(parent != nullptr)
	{
		model = parent->getModelMatrix() * localModelMatrix;
	}
	else
	{
		model = localModelMatrix;
	}
	
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
			if (shouldUpdateModel())
			{
				updateModelMatrix();
			}

			updateRotation();
		}
		else
		{
			if (shouldUpdateModel())
			{
				updateModelMatrix();
			}
			updateRotation();
		}

		updateDirectionVectors();
	}
}

void TransformComponent::render(float deltaTime, glm::mat4 view)
{
	prevPosition = position;
	prevEulerAngles = eulerAngles;
	prevRotation = rotation;
	prevScale = scale;

}

void TransformComponent::LookAt(glm::vec3 target)
{
	glm::vec3 lookVector = glm::vec3(target.x, target.y, target.z);
	if (lookVector == position) { return; }

	glm::vec3 direction = glm::normalize(lookVector - position);
	float dot = glm::dot(glm::vec3(0, 0, 1), direction);
	if (fabs(dot - (-1.0f)) < 0.000001f) {
		rotation = glm::angleAxis((float)M_PI, glm::vec3(0, 1, 0));
		return;
	}
	else if (fabs(dot - (1.0f)) < 0.000001f) {
		rotation = glm::quat();
		return;
	}

	float angle = glm::degrees(acosf(dot));

	glm::vec3 cross = glm::normalize(glm::cross(glm::vec3(0, 0, 1), direction));
	rotation = glm::normalize(glm::angleAxis(angle, cross));
	eulerAngles = (glm::eulerAngles(rotation));
	
}

glm::vec3 TransformComponent::RotationBetweenVectors(glm::vec3 start, glm::vec3 dest)
{
	start = glm::normalize(start);
	dest = glm::normalize(dest);

	float cosTheta = dot(start, dest);
	glm::vec3 rotationAxis;

	if (cosTheta < -1 + 0.001f) {
		// special case when vectors in opposite directions:
		// there is no "ideal" rotation axis
		// So guess one; any will do as long as it's perpendicular to start
		rotationAxis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), start);
		if (length2(rotationAxis) < 0.01) // bad luck, they were parallel, try again!
			rotationAxis = glm::cross(glm::vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return glm::degrees(glm::eulerAngles(angleAxis(glm::radians(180.0f), rotationAxis)));
	}

	rotationAxis = cross(start, dest);

	float s = sqrt((1 + cosTheta) * 2);
	float invs = 1 / s;

	return glm::degrees(glm::eulerAngles(glm::quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
	)));
}


bool TransformComponent::shouldUpdateModel()
{
	if (position != prevPosition)
	{
		return true;
	}
	else if (rotation != prevRotation)
	{
		return true;
	}
	else if (eulerAngles != prevEulerAngles)
	{
		return true;
	}
	else if (scale != prevScale)
	{
		return true;
	}

	return false;
}