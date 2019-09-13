#include "Vector3.h"
#include <stdio.h>
#include "PhysicsBody.h"

int main(int args, char argv[])
{
	PhysicsBody * Jetski = new PhysicsBody(200);

	float tick = 0;

	printf("Time(s)\t\tForce(N)\tAcceleration(m/s2)\tVelocity(m/s)\tPosition(m)\n");

	FVector3 EngineForce = FVector3(0,0,0);

	for (float i = 0; i <= 15; i += 0.5f)
	{
		if (i < 5.5)
		{
			EngineForce = FVector3(500, 0, 0);
		}
		else if (i >= 10 && Jetski->Velocity.GetAngle(FVector3(1, 0, 0)) <= 90)
		{
			EngineForce = FVector3(-625, 0, 0);
		}
		else
		{
			EngineForce = (0, 0, 0);
		}

		Jetski->AddForce(EngineForce);
		if (Jetski->Velocity.x < 0) Jetski->Velocity = FVector3(0);
		Jetski->Update(tick);

		printf("%f\t%f\t%f\t\t%f\t%f\t\n", i, EngineForce.x, Jetski->Acceleration.x, Jetski->Velocity.Length(), Jetski->Transform.Position.Length());

		tick = 0.5;
	}

	delete Jetski;

	getchar();
}