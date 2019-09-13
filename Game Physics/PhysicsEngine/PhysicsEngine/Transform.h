#pragma once
#include "Quaternion.h"
#include "Vector3.h"

class FTransform
{
public:
	//Constructors

	FTransform();

	FTransform(FVector3 InPosition, FVector3 InScale, FQuaternion InRotation);

	~FTransform();
	
	FVector3 Position;
	FVector3  Scale;
	FQuaternion Rotation;

};
