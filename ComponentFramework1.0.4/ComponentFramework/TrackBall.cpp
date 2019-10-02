#include "TrackBall.h"
#include "VMath.h"


TrackBall::TrackBall(float windowHeight, float windowLenght)
{
	WindowHeight = windowHeight;
	WindowLength = windowLenght;
}


TrackBall::~TrackBall()
{
}

Rotation TrackBall::GetRotation(Vec2 Pos1, Vec2 Pos2)
{
	Rotation rotation;
	Vec3 V1 = Vec3(Pos1.x + WindowLength * 0.5f, Pos1.y, 0.0f + WindowHeight * 0.5f);
	Vec3 V2 = Vec3(Pos2.x, Pos2.y, 0.0f);
	Vec3 Normal;
	float Angle;

	if ((V1.x*V1.x) + (V1.y*V1.y) <= 1)
	{
		V1.z = sqrt(SphereRadius - ((V1.x*V1.x) + (V1.y*V1.y)));
	}
	else
	{
		V1.z = (SphereRadius * 0.5f) / ((V1.x*V1.x) + (V1.y*V1.y));
	}

	if ((V2.x*V2.x) + (V2.y*V2.y) <= 1)
	{
		V2.z = sqrt(SphereRadius - ((V2.x*V2.x) + (V2.y*V2.y)));
	}
	else
	{
		V2.z = (SphereRadius * 0.5f) / ((V2.x*V2.x) + (V2.y*V2.y));
	}

	Angle = 1.0f / cos(VMath::dot(V1, V2));
	Normal = VMath::cross(V1, V2);

	rotation.Value = cos(Angle * 0.5f);
	rotation.Orientation = sin(Angle * 0.0f) * Normal;

	return rotation;
}