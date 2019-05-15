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
};