#ifndef TRACKBALL_H
#define TRACKBALL_H

#include "Vector.h"
#include <SDL.h>
using namespace MATH;

struct Rotation
{
	float Value = 0.0f;
	Vec3 Orientation = Vec3(0.0f);
};

class TrackBall
{
private:
	float SphereRadius = 1.0f;
	Vec3 SpherePosition = Vec3(0.0f);

	float WindowLength, WindowHeight = 0.0f;

public:
	TrackBall(float windowHeight = 0.0f, float windowLenght = 0.0f);
	~TrackBall();
	Rotation GetRotation(Vec2 Pos1, Vec2 Pos2);
};
#endif

