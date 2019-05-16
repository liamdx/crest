#pragma once

class Vector3
{
public:

	Vector3() { x = 0.0; y = 0.0; z = 0.0; };
	Vector3(float init)
	{
		z = init;
		y = init;
		x = init;
	}

	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	~Vector3() {};

	Vector3 operator +(Vector3 other)
	{
		Vector3 a = *this;
		a.x += other.x;
		a.y += other.y;
		a.z += other.z;
		return(a);
	}

	Vector3 operator -(Vector3 other)
	{
		Vector3 a = *this;
		a.x -= other.x;
		a.y -= other.y;
		a.z -= other.z;
		return(a);
	}

	Vector3 operator *(Vector3 other)
	{
		Vector3 a = *this;
		a.x *= other.x;
		a.y *= other.y;
		a.z *= other.z;
		return(a);
	}

	float dot(Vector3 b)
	{
		return ((x*b.x) + (y * b.y) + (z * b.z));
	}

	float magnitude()
	{
		return((sqrt(pow(x , 2.0)) + (pow(y, 2.0)) + (pow(z, 2.0))));	
	}


	Vector3* cross(Vector3* b)
	{
		return(new Vector3((y * b->z) - (z * b->y), (z * b->x) - (x * b->z), (x * b->y) - (y * b->x)));
	}

	Vector3 cross(Vector3 b)
	{
		return(Vector3((y * b.z) - (z * b.y), (z * b.x) - (x * b.z), (x * b.y) - (y * b.x)));
	}

	void Normalize()
	{
		float length = magnitude();
		x /= length;
		y /= length;
		z /= length;
	}

	float GetX() { return x; }
	float GetY() { return y; }
	float GetZ() { return z; }

	float x, y, z;



};