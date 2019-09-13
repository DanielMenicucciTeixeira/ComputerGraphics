#include "Vector3.h"
#include <cmath>

///Constructors

//Constructor using initial values for each component.
FVector3::FVector3(float inX, float inY, float inZ)
{
	x = inX;
	y = inY;
	z = inZ;
}

//Constructor initializing all components to a single float value.
FVector3::FVector3(float Float)
{
	x = y = z = Float;
}

//Default Constructor, initializes all values to 0;
FVector3::FVector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

///Destructors

FVector3::~FVector3()
{
}

///Operators

//Overload of the "+" operator, makes a vector plus vector addition.
FVector3 FVector3::operator+(FVector3 Vector)
{
	FVector3 Result;

	Result.x = x + Vector.x;
	Result.y = y + Vector.y;
	Result.z = z + Vector.z;

	return Result;
}

//Overload of the "+=" operator, makes a vector plus vector addition changing the current vector to equal to sum.
void FVector3::operator+=(FVector3 Vector)
{
	x += Vector.x;
	y += Vector.y;
	z += Vector.z;
}

//Overload of the "-=" operator, makes a vector minus vector subtraction. changing the current vector to equal the result.
void FVector3::operator-=(FVector3 Vector)
{
	x -= Vector.x;
	y -= Vector.y;
	z -= Vector.z;
}

//Overload of the "-" operator, makes a vector minus vector subtraction.
FVector3 FVector3::operator-(FVector3 Vector)
{

	FVector3 Result;

	Result.x = x - Vector.x;
	Result.y = y - Vector.y;
	Result.z = z - Vector.z;

	return Result;
}

//Overload of the "*" operator, makes a vector times scalar multiplication.
FVector3 FVector3::operator*(float Multiplier)
{
	FVector3 Result;

	Result.x = x * Multiplier;
	Result.y = y * Multiplier;
	Result.z = z * Multiplier;

	return Result;
}

FVector3 FVector3::operator/(float Divisor)
{
	FVector3 Result;

	Result.x = x / Divisor;
	Result.y = y / Divisor;
	Result.z = z / Divisor;

	return Result;
}

//Overload of the "*" operator, makes a vector times vector dot product.
float FVector3::operator*(FVector3 Vector)
{
	return (x*Vector.x + y*Vector.y + z*Vector.z);
}

//Overload of the "=" operator, makes each component of the vector equal to the equivalent component of a given vector.
void FVector3::operator=(FVector3 Vector)
{
	x = Vector.x;
	y = Vector.y;
	z = Vector.z;
}

///Functions

//Returns the magnitude of the Vector (or Vector's scalar lenght)
float FVector3::Length()
{
	return sqrt(x*x + y * y + z * z);
}

//Returns the angle between this vector and another given vector in degrees.
float FVector3::GetAngle(FVector3 Vector)
{
	FVector3 thisVector;
	thisVector.x = x;
	thisVector.y = y;
	thisVector.z = z;
	
	return acos((thisVector * Vector)/(thisVector.Length() * Vector.Length())) * 180.0f/ 3.14159265f;
}

//Returns the angle between this vector and another given vector in radians.
float FVector3::GetRadAngle(FVector3 Vector)
{
	FVector3 thisVector;
	thisVector.x = x;
	thisVector.y = y;
	thisVector.z = z;

	return acos((thisVector * Vector) / (Length() * Vector.Length()));
}

//Returns the Cross product of this vector and another given vector.
FVector3 FVector3::CrossProduct(FVector3 Vector)
{
	return FVector3(y*Vector.z - z*Vector.y, z*Vector.x - x*Vector.z, x*Vector.y - y*Vector.x);
}

FVector3 FVector3::Lerp(FVector3 Vector, float alpha)
{
	FVector3 ThisVector(x, y, z);

	if (alpha < 0) alpha = 0;
	if (alpha > 1) alpha = 1;
	//TODO Output warning that alpha has been changed to 0 or 1 due to it being out of bounds

	return (ThisVector * alpha) - (Vector * (1-alpha));
}
