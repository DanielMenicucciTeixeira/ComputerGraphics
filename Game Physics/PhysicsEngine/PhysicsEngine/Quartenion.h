#pragma once
#include "Vector3.h"

class FQuartenion
{
public:

	float x, y, z, w;

	//Constructors
	FQuartenion();
	FQuartenion(float X, float Y, float Z, float W);
	FQuartenion(FVector3 Axis, float W);
	FQuartenion(FVector3 Axis);

	//Destructors
	~FQuartenion();
};
