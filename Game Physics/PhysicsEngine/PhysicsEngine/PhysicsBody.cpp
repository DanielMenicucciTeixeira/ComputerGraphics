#include "PhysicsBody.h"

///Constructors

//Default contructor, sets all components to 0.
PhysicsBody::PhysicsBody()
{
	Transform = FTransform();
	Velocity = FVector3();
	Acceleration = FVector3();
	Mass = 0.0f;
}

//Set each compoenent to a given value.
PhysicsBody::PhysicsBody(FTransform InTrasform, FVector3 InVelocity, FVector3 InAcceleration, float InMass)
{
	Transform = InTrasform;
	Velocity = InVelocity;
	Acceleration = InAcceleration;
	Mass = InMass;
}

//Set each component to a given value, transform is set to given position with rotation (0,0,0) and scale (1,1,1).
PhysicsBody::PhysicsBody(FVector3 InPosition, FVector3 InVelocity, FVector3 InAcceleration, float InMass)
{
	Transform = FTransform(InPosition, FVector3(1,1,1), FQuaternion());
	Velocity = InVelocity;
	Acceleration = InAcceleration;
	Mass = InMass;
}

//Sets mass to given value, all other compoents to 0.
PhysicsBody::PhysicsBody(float InMass)
{
	Transform = FTransform();
	Velocity = FVector3();
	Acceleration = FVector3();
	Mass = InMass;
}

///Destructors

PhysicsBody::~PhysicsBody()
{
}

///Functions

//This functions should be called every frame to calculate trasform and velocity, delta time is the time interval between frames.
void PhysicsBody::Update(float DeltaTime)
{
	Transform.Position += Velocity*DeltaTime + (Acceleration * DeltaTime*DeltaTime)*0.5;
	Velocity += Acceleration * DeltaTime;
	Acceleration = AppleidForce / Mass;
	AppleidForce = 0;
}

//Recalculates Acceleration given a force vector.
void PhysicsBody::AddForce(FVector3 Force)
{
	AppleidForce += Force;
}
