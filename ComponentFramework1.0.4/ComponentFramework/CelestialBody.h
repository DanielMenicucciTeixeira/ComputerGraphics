#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "GameObject.h"

enum Axis
{
	X,
	Y,
	Z
};

class CelestialBody : public GameObject
{
protected:

	float RotationSpeed = 0.0f;
	float rotation = 0.0f;
	Vec3 RotationOrientation = Vec3(0.0f);
	
	float RevolutionRadius = 0.0f;

	float RevolytionAngularSpeed = 0.0f;
	float RevolutionAngle = 0.0f;
	Axis RevolutionAxis = Z;
	
	Vec3 Scale = Vec3(1.0f);
	
	GameObject * GravityCenter = nullptr;

	float Pi = 22.0f / 7.0f;


	MATH::Matrix4 RevolutionTranslation(Axis axis, float positionX, float positionY);

	

public:

	void Update(float deltaTime);

	void SetRotation(float speed, Vec3 orientation);
	void SetRevolution(float speed, Axis axis);
	void SetScale(float scale);
	void SetGravityCenter(GameObject * gravityCenter);

	float GetRotationSpeed();


	CelestialBody(Mesh *mesh_, Shader *shader_, Texture *texture_);
	~CelestialBody();

};
#endif

