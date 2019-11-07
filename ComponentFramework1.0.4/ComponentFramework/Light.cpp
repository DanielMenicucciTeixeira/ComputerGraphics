#include "Light.h"
#include <iostream>
#include "Shader.h"


Light::Light(Shader * _shader):GameObject(Vec3(0.0, 0.0, 0.0), _shader)
{
	Colour = Vec4(1.0, 1.0, 1.0, 0.0);
	Intensity = 1.0;
}

Light::Light(Vec4 colour, float intensity, Vec3 position, Shader * _shader):GameObject(position, _shader)
{
	Colour = colour;
	Intensity = intensity;
}

Light::~Light()
{
}

void Light::RenderLights(std::vector<Light*> LightSources)
{
	for (int i = 0; i < LightSources.size(); i++)
	{
		if (LightSources[i] != nullptr)
		{
			//each variable beyond the first is located one unit after the prior varible, just like in the array, so this just parses through them, one by one, setting the Position values
			glUniform3fv(shader->getUniformID("lightPos[0]") + i, 1, LightSources[i]->Position);
			glUniform4fv(shader->getUniformID("lightColour[0]") + i, 1, LightSources[i]->GetColour() * LightSources[i]->GetIntensity());
		}
	}
}
