#pragma once


class Matrix4
{
public:

	Matrix4() { a1 = 0; a2 = 0; a3 = 0; a4 = 0;
	b1 = 0; b2 = 0; b3 = 0; b4 = 0;
	c1 = 0; c2 = 0; c3 = 0; c4 = 0;
	d1 = 0; d2 = 0; d3 = 0; d4 = 0;
	};

	Matrix4(float _a1, float _a2, float _a3, float _a4,
		float _b1, float _b2, float _b3, float _b4,
		float _c1, float _c2, float _c3, float _c4,
		float _d1, float _d2, float _d3, float _d4)
	{
		a1 = _a1; a2 = _a2; a3 = _a3; a4 = _a4;
		b1 = _b1; b2 = _b2; b3 = _b3; b4 = _b4;
		c1 = _c1; c2 = _c2; c3 = _c3; c4 = _c4;
		d1 = _d1; d2 = _d2; d3 = _d3; d4 = _d4;
	}


	Matrix4 operator *(Matrix4 b)
	{
		Matrix4 a = *this;

		a1 = ((a.a1 * b.a1) + (a.a2 * b.b1) + (a.a3 * b.c1) + (a.a4 * b.d1));
		a2 = ((a.a1 * b.a2) + (a.a2 * b.b2) + (a.a3 * b.c2) + (a.a4 * b.d2));
		a3 = ((a.a1 * b.a3) + (a.a2 * b.b3) + (a.a3 * b.c3) + (a.a4 * b.d3));
		a4 = ((a.a1 * b.a4) + (a.a2 * b.b4) + (a.a3 * b.c4) + (a.a4 * b.d4));

		b1 = ((a.b1 * b.a1) + (a.b2 * b.b1) + (a.b3 * b.c1) + (a.b4 * b.d1));
		b2 = ((a.b1 * b.a2) + (a.b2 * b.b2) + (a.b3 * b.c2) + (a.b4 * b.d2));
		b3 = ((a.b1 * b.a3) + (a.b2 * b.b3) + (a.b3 * b.c3) + (a.b4 * b.d3));
		b4 = ((a.b1 * b.a4) + (a.b2 * b.b4) + (a.b3 * b.c4) + (a.b4 * b.d4));

		c1 = ((a.c1 * b.a1) + (a.c2 * b.b1) + (a.c3 * b.c1) + (a.c4 * b.d1));
		c2 = ((a.c1 * b.a2) + (a.c2 * b.b2) + (a.c3 * b.c2) + (a.c4 * b.d2));
		c3 = ((a.c1 * b.a3) + (a.c2 * b.b3) + (a.c3 * b.c3) + (a.c4 * b.d3));
		c4 = ((a.c1 * b.a4) + (a.c2 * b.b4) + (a.c3 * b.c4) + (a.c4 * b.d4));

		d1 = ((a.d1 * b.a1) + (a.d2 * b.b1) + (a.d3 * b.c1) + (a.d4 * b.d1));
		d2 = ((a.d1 * b.a2) + (a.d2 * b.b2) + (a.d3 * b.c2) + (a.d4 * b.d2));
		d3 = ((a.d1 * b.a3) + (a.d2 * b.b3) + (a.d3 * b.c3) + (a.d4 * b.d3));
		d4 = ((a.d1 * b.a4) + (a.d2 * b.b4) + (a.d3 * b.c4) + (a.d4 * b.d4));

		return(Matrix4(a1, a2, a3, a4, b1, b2, b3, b4, c1, c2, c3, c4, d1, d2, d3, d4));
	}


	void Print()
	{
		std::cout << "ABCD COLUMNS, 1234 ROWS" << std::endl;
		std::cout << "a1:" << a1 << " a2:" << a2 << " a3:" << a3 << " a4:" << a4 << std::endl;
		std::cout << "b1:" << b1 << " b2:" << b2 << " b3:" << b3 << " b4:" << b4 << std::endl;
		std::cout << "c1:" << c1 << " c2:" << c2 << " c3:" << c3 << " c4:" << c4 << std::endl;
		std::cout << "d1:" << d1 << " d2:" << d2 << " d3:" << d3 << " d4:" << d4 << std::endl;
	}

	float a1, a2, a3, a4,
		b1, b2, b3, b4,
		c1, c2, c3, c4,
		d1, d2, d3, d4;
};