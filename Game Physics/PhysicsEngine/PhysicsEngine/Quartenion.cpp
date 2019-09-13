#include "Quartenion.h"

//Constructors

FQuartenion::FQuartenion()
{
	x = y = z = w = 0.0f;
}

FQuartenion::FQuartenion(float X, float Y, float Z, float W)
{
	x = X;
	y = Y;
	z = Z;
	w = W;
}

FQuartenion::FQuartenion(FVector3 Axis, float W)
{
	x = Axis.x;
	y = Axis.y;
	z = Axis.z;
	w = W;
}

FQuartenion::FQuartenion(FVector3 Axis)
{
	x = Axis.x;
	y = Axis.y;
	z = Axis.z;
	
	w = 0.0f;
}

//Destructors

FQuartenion::~FQuartenion()
{
}
