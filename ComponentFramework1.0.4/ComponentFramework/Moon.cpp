#include "Moon.h"
#include "MMath.h"



void Moon::Update(float deltaTIme)
{
	rotation += RotationSpeed;

	//Need to convert the rotation from degrees to radians for the cos and sin methods
	float RevolutionX = (cos(rotation * (Pi / 180)) * RevolutionRadius) + GravityCenter->GetPosition().x;//The cos of the radian is the cartisian coordinate for X with circle of radius 1
	float RevolutionY = (sin(rotation * (Pi / 180)) * RevolutionRadius) + GravityCenter->GetPosition().y;//The sin of the radian is the cartisian coordinate for Y with circle of radius 1

	//Scales, Translates and rotates the object
	setModelMatrix(MMath::scale(Scale) * MMath::rotate(-90, Vec3(1.0, 0.0, 0.0)) * MMath::rotate(rotation, RotationOrientation)* RevolutionTranslation(RevolutionAxis, RevolutionX, RevolutionY));
}

Moon::Moon(Mesh *mesh_, Shader *shader_, Texture *texture_):CelestialBody(mesh_, shader_, texture_)
{
}


Moon::~Moon()
{
}
