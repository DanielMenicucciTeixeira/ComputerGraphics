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

void CelestialBody::SetRevolution(float speed, Axis axis, GameObject * gravityCenter, float radius, float elipticalProportion)
{
	RevolutionSpeed = speed;
	RevolutionAxis = axis;
	GravityCenter = gravityCenter;
	RevolutionRadius = radius;
}

void CelestialBody::SetScale(float scale)
{
	Scale = Scale * scale;
}

void CelestialBody::SetGravityCenter(GameObject * gravityCenter)
{
	GravityCenter = gravityCenter;
}

void CelestialBody::SetRotationTilt(float angle, Vec3 orientation)
{
	RotationTiltAngle = angle;
	RotationTiltOrientation = orientation;
}

void CelestialBody::addSatelite(CelestialBody * satelite)
{
	SateliteList.push_back(satelite);
}

float CelestialBody::GetRotationSpeed()
{
	return RotationSpeed;
}

void CelestialBody::Update(float deltaTime)
{
	/*

	RotationAngle += RotationSpeed * deltaTime;
	RevolutionAngle += RevolutionSpeed * deltaTime;
	
	if (GravityCenter != nullptr)
	{
		
		//Need to convert the from degrees to radians for the cos and sin methods
		float RevolutionX = GravityCenter->GetPosition().x + (cos(RevolutionAngle * (Pi / 180)) * RevolutionRadius);//Movemennt in the orbits X axis, in case of an elipse, this is the base radius
		float RevolutionY = GravityCenter->GetPosition().y + (sin(RevolutionAngle * (Pi / 180)) * RevolutionRadius * ElipticalProportion);//Movement in the orbits Y axis, in case of an elipse, this radius is a multiple of the X angle

		Position = Vec3
		(
			RevolutionTranslation(RevolutionAxis, RevolutionX, RevolutionY)[13],
			RevolutionTranslation(RevolutionAxis, RevolutionX, RevolutionY)[14],
			RevolutionTranslation(RevolutionAxis, RevolutionX, RevolutionY)[15]
		);
		
		setModelMatrix//The order of the following matrix multiplications is not arbitrary and should not be changed
		(
			  MMath::rotate(-90, Vec3(1.0, 0.0, 0.0))//Fix model's base rotation if necessery, to align it to cartesian volume
			* RevolutionTranslation(RevolutionAxis, RevolutionX, RevolutionY) //Place model in correct position
		    * MMath::rotate(RotationAngle, RotationOrientation)
			* MMath::rotate(RotationTiltAngle, RotationTiltOrientation)//Afeter rotation is done, apply disired tilt angle
			* MMath::scale(Scale)//Scale the model to desired size
		);
	}
	else
	{
		Position = Vec3(1.0f, 0.0f, 1.0f);

		//Simillar to the equation above, same restrictions to order of multiplication, but this does not include translation
		setModelMatrix
		(
			  MMath::rotate(-90, Vec3(1.0, 0.0, 0.0))//Fix models base rotation if necessery, to align it to cartesian volume
			* MMath::rotate(RotationAngle, RotationOrientation)//Fix models base rotation if necessery, to align it to cartesian volume
			* MMath::rotate(RotationTiltAngle, RotationTiltOrientation)//Afeter rotation is done, apply disired tilt angle
			* MMath::scale(Scale)//Scale the model to desired size
		);

	}
	*/
	RotationAngle += RotationSpeed * deltaTime;
	RevolutionAngle += RevolutionSpeed * deltaTime;

	//Movemennt in the orbits X axis, in case of an elipse, this is the base radius
	Position.x = (cos(RevolutionAngle * (Pi / 180)) * RevolutionRadius);
	//Movement in the orbits Y axis, in case of an elipse, this radius is a multiple of the X angle
	Position.y = (sin(RevolutionAngle* (Pi / 180)) * RevolutionRadius * ElipticalProportion);
	if (GravityCenter != nullptr)
	{
		Position.x += GravityCenter->Position.x;
		Position.y += GravityCenter->Position.y;
		Position.z = GravityCenter->Position.z;

		setModelMatrix//The order of the following matrix multiplications is not arbitrary and should not be changed
		(
			  MMath::rotate(-90, Vec3(1.0, 0.0, 0.0))//Fix model's base rotation if necessery, to align it to cartesian volume
			* MMath::translate(Position) //Place model in correct position
			* MMath::rotate(RotationAngle, RotationOrientation)//Rotate the model the disired amount
			* MMath::rotate(RotationTiltAngle, RotationTiltOrientation)//Afeter rotation is done, apply disired tilt angle
			* MMath::scale(Scale)//Scale the model to desired size
		);
	}
	else
	{
		setModelMatrix//The order of the following matrix multiplications is not arbitrary and should not be changed
		(
			  MMath::rotate(-90, Vec3(1.0, 0.0, 0.0))//Fix model's base rotation if necessery, to align it to cartesian volume
			* MMath::rotate(RotationAngle, RotationOrientation)//Rotate the model the disired amount
			* MMath::rotate(RotationTiltAngle, RotationTiltOrientation)//Afeter rotation is done, apply disired tilt angle
			* MMath::scale(Scale)//Scale the model to desired size
		);
	}
}

CelestialBody::CelestialBody(Mesh *mesh_, Shader *shader_, Texture *texture_):GameObject(mesh_,shader_, texture_)
{
}

CelestialBody::CelestialBody(Mesh * mesh_, Shader * shader_, const char texturePath[]) : GameObject(mesh_, shader_, texturePath)
{
}


CelestialBody::~CelestialBody()
{
	delete(GravityCenter); GravityCenter = nullptr;
}
