#pragma once

class FVector3
{
public:

	//Variables (coordinates of the vector)
	float x, y, z;

	///Constructors

	//Constructor using initial values for each component.
	FVector3(float X, float Y, float Z);

	//Constructor initializing all components to a single float value.
	FVector3(float Float);

	//Default Constructor, initializes all values to 0;
	FVector3();

	///Destructor

	~FVector3();

	///Operators

	FVector3 operator+ (FVector3 Vector);//Overload of the "+" operator, makes a vector plus vector addition.

	FVector3 operator- (FVector3 Vector);//Overload of the "-" operator, makes a vector minus vector subtraction.

	FVector3 operator* (float Multiplier);//Overload of the "*" operator, makes a vector times scalar multiplication.

	FVector3 operator/ (float Divisor);//Overload of the "/" operator, makes a vector divided by scalar division.

	float operator* (FVector3 Vector);//Overload of the "*" operator, makes a vector times vector dot product.

	void operator= (FVector3 Vector);//Overload of the "=" operator, makes each component of the vector equal to the equivalent component of a given vector.

	void operator+= (FVector3 Vector);//Overload of the "+=" operator, makes a vector plus vector addition changing the current vector to equal to sum.

	void operator-= (FVector3 Vector);//Overload of the "-=" operator, makes a vector minus vector subtraction. changing the current vector to equal the result.

	///Functions

	//Returns the magnitude of the Vector (or Vector's scalar lenght)
	float Length();

	//Returns the angle between this vector and another given vector in degrees.
	float GetAngle(FVector3 Vector);

	//Returns the angle between this vector and another given vector in radians.
	float GetRadAngle(FVector3 Vector);

	//Returns the cross product between this vector and another given vector.
	FVector3 CrossProduct(FVector3 Vector);

	//Interpolates linearly between the two vectors given an alpha between 0 and 1, in the case of position vectors, 
	//alpha should be time spent divided by the time between the initial and final position.
	//In any case alpha is the fraction of the total "movement" from the first vector to the second.
	FVector3 Lerp(FVector3 Vector, float alpha);

};
