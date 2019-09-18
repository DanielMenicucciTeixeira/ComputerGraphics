#include "CelestialBody.h"
#include "MMath.h"



MATH::Matrix4 CelestialBody::RevolutionTranslation(Axis axis, float position1, float position2)
{
	switch (axis)
	{
		case X: return  MMath::translate(0.0f, position2, position1);
		case Y: return  MMath::translate(position2, 0.0f, position1);
		case Z: return  MMath::translate(position1, position2, 0.0f);
		default: return MATH::Matrix4();
	}
}

void CelestialBody::SetRotation(float speed, Vec3 orientation)
{
	RotationSpeed = speed;
	RotationOrientation = orientation;
}

void CelestialBody::SetRevolution(float speed, Axis axis)
{
	RevolytionAngularSpeed = speed;
	RevolutionAxis = axis;
}

void CelestialBody::SetScale(float scale)
{
	Scale = Scale * scale;
}

void CelestialBody::SetGravityCenter(GameObject * gravityCenter)
{
	GravityCenter = gravityCenter;
}

float CelestialBody::GetRotationSpeed()
{
	return RotationSpeed;
}

void CelestialBody::Update(float deltaTime)
{
	rotation += RotationSpeed;
	RevolutionAngle += RevolytionAngularSpeed;

	if (GravityCenter != nullptr)
	{
		//Need to convert the from degrees to radians for the cos and sin methods
		float RevolutionX = (cos(RevolutionAngle * (Pi / 180)) * RevolutionRadius) + GravityCenter->GetPosition().x;
		float RevolutionY = (sin(RevolutionAngle * (Pi / 180)) * RevolutionRadius) + GravityCenter->GetPosition().y;

		setModelMatrix(MMath::scale(Scale) * MMath::rotate(-90, Vec3(1.0, 0.0, 0.0)) * MMath::rotate(rotation, RotationOrientation)* RevolutionTranslation(RevolutionAxis, RevolutionX, RevolutionY));
	}
	else
	{
		setModelMatrix(MMath::scale(Scale) * MMath::rotate(-90, Vec3(1.0, 0.0, 0.0)) * MMath::rotate(rotation, RotationOrientation));
	}
	
}

CelestialBody::CelestialBody(Mesh *mesh_, Shader *shader_, Texture *texture_):GameObject(mesh_,shader_, texture_)
{
}


CelestialBody::~CelestialBody()
{
	delete(GravityCenter); GravityCenter = nullptr;
}
