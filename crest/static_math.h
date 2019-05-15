#pragma once



static class CrestMaths
{
	static double pi()
	{
		return(3.14159265359);
	}

	static float radians(float degrees) 
	{

		return(degrees * (pi() / 180));

	}
};