#include "Light.h"


Light::Light()
{
	Colour = Vec4(1.0, 1.0, 1.0, 0.0);
	Intensity = 1.0;
	Position = Vec3(0.0, 0.0, 0.0);
}

Light::Light(Vec4 colour, float intensity, Vec3 position)
{
	Colour = colour;
	Intensity = intensity;
	Position = position;
}

Light::~Light()
{
}
