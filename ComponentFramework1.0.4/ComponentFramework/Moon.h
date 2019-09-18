#ifndef MOON_H
#define MOON_H

#include "CelestialBody.h"
class Moon : public CelestialBody
{

public:
	void Update(float deltaTIme);

	GameObject * Planet = nullptr;

	Moon(Mesh *mesh_, Shader *shader_, Texture *texture_);
	~Moon();
};
#endif
