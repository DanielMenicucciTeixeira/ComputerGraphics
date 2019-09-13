#include "Vector3.h"
#include <cmath>

Vector3::Vector3(float inX, float inY, float inZ)
{
	x = inX;
	y = inY;
	z = inZ;
}

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3 Vector3::Add(Vector3 Vector)
{
	Vector3 Result;

	Result.x = x + Vector.x;
	Result.y = y + Vector.y;
	Result.z = z + Vector.z;

	return Result;
}

Vector3 Vector3::Subtract(Vector3 Vector)
{
	Vector3 Result;

	Result.x = x - Vector.x;
	Result.y = y - Vector.y;
	Result.z = z - Vector.z;

	return Result;
}

Vector3 Vector3::Multiply(float Multiplier)
{
	Vector3 Result;

	Result.x = x * Multiplier;
	Result.y = y * Multiplier;
	Result.z = z * Multiplier;

	return Result;
}

float Vector3::Magnitude()
{
	return sqrt(x*x + y*y + z*z);
}
