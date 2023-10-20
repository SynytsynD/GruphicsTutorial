#include "graphics_math.h"


v2 V2 (double Arg)
{
	v2 Result = {};
	Result.x = Arg;
	Result.y = Arg;
	return Result;
}

v2 V2 (double X, double Y) 
{
	v2 Result = {};
	Result.x = X;
	Result.y = Y;
	return Result;
}

v2 operator+ (v2 A, v2 B)
{
	v2 Result = {};
	Result.x = A.x + B.x;
	Result.y = A.y + B.y;
	return Result;
}

v2 operator* (v2 A, v2 B)
{
	v2 Result = {};
	Result.x = A.x * B.x;
	Result.y = A.y * B.y;
	return Result;
}

v2 operator* (double A, v2 B)
{
	v2 Result = {};
	Result.x = A * B.x;
	Result.y = A * B.y;
	return Result;
}

v2 operator/ (v2 A, double B)
{
	v2 Result = {};
	Result.x = A.x / B;
	Result.y = A.y / B;
	return Result;
}

v3 V3 (double X, double Y, double Z)
{
	v3 Result = {};

	Result.x = X;
	Result.y = Y;
	Result.z = Z;

	return Result;
}
	
v3 operator+(v3 A, v3 B)
{
	v3 result = {};
	result.x = A.x + B.x;
	result.y = A.y + B.y;
	result.z = A.z + B.z;

	return result;
}