#pragma once
#include "Transform.h"
#include "Vector3.h"

class PhysicsBody
{

public:

	///Variables

	//Stores position, rotation and scale of the physics body
	FTransform Transform;

	//The physics body current speed in m/s with direction
	FVector3 Velocity;

	//Resulting acceleration in m/s2 currently afecting this physics body, used to update the velocity
	FVector3 Acceleration;

	//This physics body mass in kg
	float Mass;

	//Force being applyied on this body
	FVector3 AppleidForce;

	///Constructors
	
	//Default contructor, sets all components to 0.
	PhysicsBody();

	//Set each compoenent to a given value.
	PhysicsBody(FTransform InTrasform, FVector3 InVelocity, FVector3 InAcceleration, float InMass);

	//Set each component to a given value, transform is set to given position with rotation (0,0,0) and scale (1,1,1).
	PhysicsBody(FVector3 InPosition, FVector3 InVelocity, FVector3 InAcceleration, float InMass);

	//Sets mass to given value, all other compoents to 0.
	PhysicsBody(float InMass);
	
	///Destructors
	~PhysicsBody();

	///Functions

	//This functions should be called every frame to calculate and update trasform and velocity, delta time is the time interval between frames.
	void Update(float DeltaTime);

	//Recalculates Acceleration given a force vector.
	void AddForce(FVector3 Force);
};