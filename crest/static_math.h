#pragma once

static class CrestMaths
{
public:
	static double pi()
	{
		return(3.14159265359);
	}

	static float radians(float degrees) 
	{
		return(degrees * (pi() / 180));
	}

	static auto GLVec3(Vector3 v)
	{
		const GLfloat glVec[] = { v.GetX(), v.GetY(), v.GetZ() };
		return glVec;
	}

	static auto GLMat4(Matrix4 m)
	{
		const GLfloat glMat[] = {m.a1,m.a2,m.a3,m.a4,
								m.b1,m.b2,m.b3,m.b4,
								m.c1,m.c2,m.c3,m.c4,
								m.d1,m.d2,m.d3, m.d4};
		return glMat;
	}

	static Vector3 normalize(Vector3 a)
	{
		float length = a.magnitude();
		float x = a.GetX() / length;
		float y = a.GetY() / length;
		float z = a.GetZ() / length;
		return(Vector3(x, y, z));
	}

	static Vector3 cross(Vector3 a, Vector3 b)
	{
		return(Vector3((a.GetY() * b.GetZ()) - (a.GetZ() * b.GetY()), (a.GetZ() * b.GetX()) - (a.GetX() * b.GetZ()), (a.GetX() * b.GetY()) - (a.GetY() * b.GetX())));
	}

	static Matrix4 translate(Vector3 position)
	{
		Matrix4 translation; // Identity matrix by default
		translation.c1 = -position.x; // Third column, first row
		translation.c2 = -position.y;
		translation.c3 = -position.z;
	}

	static Matrix4 rotate(Vector3 position)
	{

	}

	static Matrix4 debugProjectionMatrix()
	{
		return(Matrix4(0.347270, 0.000000, 0.000000, 0.000000,
			0.000000, 0.617370, 0.000000, 0.000000,
			0.000000, 0.000000, -1.001001, -1.000000,
			0.000000, 0.000000, -0.200100, 0.000000));
	}
};