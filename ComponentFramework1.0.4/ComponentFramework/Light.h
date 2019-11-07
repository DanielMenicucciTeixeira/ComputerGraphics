#ifndef LIGHT_H
#define LIGHT_H

#include "GameObject.h"
#include <vector>
#include "Vector.h"

using namespace MATH;
class Light : public GameObject
{
protected:
	Vec4 Colour;
	float Intensity;

public:
	Light(Shader * _shader);
	Light(Vec4 colour, float intensity, Vec3 position, Shader * _shader);
	~Light();
	void RenderLights(std::vector<Light*> LightSources);

	Vec4 GetColour() { return Colour; }
	float GetIntensity() { return Intensity; }

};
#endif



