#pragma once


class Vector2
{
public:

	Vector2() { x = 0.0; y = 0.0; };
	Vector2(float init)
	{
		y = init;
		x = init;
	}

	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	~Vector2() {};

	void operator +(Vector2 other)
	{
		x += other.x;
		y += other.y;
	}

	void operator -(Vector2 other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator *(float other)
	{
		x *= other;
		y *= other;
	}

	float dot(Vector2 b)
	{
		return ((x*b.x) + (y * b.y));
	}

	float magnitude()
	{
		return(sqrt(pow(x, 2.0) + pow(y, 2.0)));
	}

	float x, y;



};