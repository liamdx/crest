#pragma once

#include "CrestMath.h"
#include <math.h>

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:

	// Default camera values
	const float YAW = -90.0f;
	const float PITCH = 0.0f;
	const float SPEED = 2.5f;
	const float SENSITIVITY = 0.1f;
	const float ZOOM = 45.0f;

	// Camera Attributes
	Vector3 Position;
	Vector3 Front;
	Vector3 Up;
	Vector3 Right;
	Vector3 WorldUp;
	// Euler Angles
	float Yaw;
	float Pitch;
	// Camera options
	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;
	bool canMove;

	// Constructor with vectors
	Camera(Vector3 position = Vector3(0.0f, 0.0f, 0.0f), Vector3 up = Vector3(0.0f, 1.0f, 0.0f)) : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		WorldUp = up;
		Yaw = YAW;
		Pitch = PITCH;
		updateCameraVectors();
	}
	// Constructor with scalar values
	Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(Vector3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = Vector3(posX, posY, posZ);
		WorldUp = Vector3(upX, upY, upZ);
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	//// Processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
	//void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	//{
	//	if (canMove) {
	//		float velocity = MovementSpeed * deltaTime;

	//		if (direction == FORWARD)
	//			Position += Front * velocity;
	//		if (direction == BACKWARD)
	//			Position -= Front * velocity;
	//		if (direction == LEFT)
	//			Position -= Right * velocity;
	//		if (direction == RIGHT)
	//			Position += Right * velocity;
	//	}

	//}

	// Processes input received from a mouse input system. Expects the offset value in both the x and y direction.
	void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
	{
		if (canMove)
		{
			xoffset *= MouseSensitivity;
			yoffset *= MouseSensitivity;

			Yaw = xoffset;
			Pitch = yoffset;

			// Make sure that when pitch is out of bounds, screen doesn't get flipped
			if (constrainPitch)
			{
				if (Pitch > 89.0f)
					Pitch = 89.0f;
				if (Pitch < -89.0f)
					Pitch = -89.0f;
			}

			// Update Front, Right and Up Vectors using the updated Euler angles
			updateCameraVectors();
		}

	}

	// Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
	void ProcessMouseScroll(float yoffset)
	{
		if (canMove)
		{
			if (Zoom >= 1.0f && Zoom <= 45.0f)
				Zoom -= yoffset;
			if (Zoom <= 1.0f)
				Zoom = 1.0f;
			if (Zoom >= 45.0f)
				Zoom = 45.0f;
		}

	}

	// Custom implementation of the LookAt function
	Matrix4 GetViewMatrix(Vector3 position, Vector3 target, Vector3 worldUp)
	{
		// 1. Position = known
		// 2. Calculate cameraDirection
		Vector3 zaxis = position - target;
		// 3. Get positive right axis vector
		Vector3 xaxis = CrestMaths::normalize(CrestMaths::cross(CrestMaths::normalize(worldUp), zaxis));
		// 4. Calculate camera up vector
		Vector3 yaxis = CrestMaths::cross(zaxis, xaxis);

		// Create translation and rotation matrix
		// In glm we access elements as mat[col][row] due to column-major layout
		Matrix4 translation; // Identity matrix by default
		translation.c1 = -position.GetX(); // Third column, first row
		translation.c2 = -position.GetY();
		translation.c3 = -position.GetZ();
		Matrix4 rotation;
		rotation.a1 = xaxis.GetX(); // First column, first row
		rotation.b1 = xaxis.GetY();
		rotation.c1 = xaxis.GetZ();
		rotation.a2 = yaxis.GetX(); // First column, second row
		rotation.c2 = yaxis.GetY();
		rotation.a3 = zaxis.GetX(); // First column, third row
		rotation.b3 = zaxis.GetY();
		rotation.c3 = zaxis.GetZ();

		// Return lookAt matrix as combination of translation and rotation matrix
		return rotation * translation; // Remember to read from right to left (first translation then rotation)
	}





	// view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//view = calculate_lookAt_matrix(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

private:
	// Calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors()
	{
		// Calculate the new Front vector
		Vector3 front;
		float frontX = cos(CrestMaths::radians(Yaw)) * cos(CrestMaths::radians(Pitch));
		float frontY = sin(CrestMaths::radians(Pitch));
		float frontZ = sin(CrestMaths::radians(Yaw)) * cos(CrestMaths::radians(Pitch));
		Front = CrestMaths::normalize(front);
		// Also re-calculate the Right and Up vector
		Right = CrestMaths::normalize(CrestMaths::cross(Front, WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		Up = CrestMaths::normalize(CrestMaths::cross(Right, Front));
	}
};
