#include "Vector3.h"
#include <stdio.h>
#include <iostream>

Vector3 CreateVector3()
{
	float x, y, z;

	printf("x = ");
	std::cin >> x;

	printf("y = ");
	std::cin >> y;

	printf("z = ");
	std::cin >> z;

	printf("\n");

	return Vector3(x, y, z);
}

int main(int argc, char * argv[])
{
	Vector3 Vector;
	Vector3 OperationVector;
	float Multiplier;

	printf("Enter the value for the x, y and z coordinates of a vector\nEnter only interger values\n");
	Vector = CreateVector3();
	printf(" Your Vector: (%f, %f, %f) has a Magnitude of %f\n", Vector.x, Vector.y, Vector.z, Vector.Magnitude());
	
	printf("Enter a vector to be added to your vector\n");
	OperationVector = CreateVector3();
	printf("  (%f, %f, %f)\n+ (%f, %f, %f)\n= (%f, %f, %f)\n\n", Vector.x, Vector.y, Vector.z, OperationVector.x, OperationVector.y, OperationVector.z, Vector.Add(OperationVector).x, Vector.Add(OperationVector).y, Vector.Add(OperationVector).z);

	printf("Enter a vector to be subtracted from your vector\n");
	OperationVector = CreateVector3();
	printf("  (%f, %f, %f)\n- (%f, %f, %f)\n= (%f, %f, %f)\n\n", Vector.x, Vector.y, Vector.z, OperationVector.x, OperationVector.y, OperationVector.z, Vector.Subtract(OperationVector).x, Vector.Subtract(OperationVector).y, Vector.Subtract(OperationVector).z);

	printf("Enter a number to multiply your vector by\n");
	std::cin >> Multiplier;
	printf("  (%f, %f, %f)\nx %f\n= (%f,%f, %f)\n\n", Vector.x, Vector.y, Vector.z, Multiplier, Vector.Multiply(Multiplier).x, Vector.Multiply(Multiplier).y, Vector.Multiply(Multiplier).z);

	system("PAUSE");
}
