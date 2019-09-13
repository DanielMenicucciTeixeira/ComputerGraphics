#ifndef LIGHT_H
#define LIGHT_H

#include "GameObject.h"
#include "Vector.h"

using namespace MATH;
class Light
{
public:
	Light();
	Light(Vec4 colour, Vec4 intensity, Vec3 position);
	~Light();

	Vec4 Colour;
	Vec4 Intensity;
	Vec3 Position;

};
#endif



