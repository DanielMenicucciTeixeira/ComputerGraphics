#ifndef CELESTIALBODY_H
#define CELESTIALBODY_H

#include "GameObject.h"
#include <vector>

enum Axis
{
	X,
	Y,
	Z
};

class CelestialBody : public GameObject
{
protected:

	float RotationSpeed = 0.0f;//In degrees per second
	float RotationAngle = 0.0f;//In degrees
	Vec3 RotationOrientation = Vec3(0.0f, 0.0f, 1.0f);
	float RotationTiltAngle = 0.0f;
	Vec3 RotationTiltOrientation = Vec3(0.0f, 0.0f, 1.0f);
	std::vector<CelestialBody*> SateliteList;
	
	float RevolutionRadius = 0.0f;
	float RevolutionSpeed = 0.0f;//In degrees per second
	float RevolutionAngle = 0.0f;//In degrees
	float ElipticalProportion = 1.0f;//Size of Y axis of the elipse in relation to X, value of 1 means a circle.
	Axis RevolutionAxis = Z;

	Vec3 Scale = Vec3(1.0f);
	
	GameObject * GravityCenter = nullptr;

	float Pi = 22.0f / 7.0f;

	bool IsSatelite = false;


	MATH::Matrix4 RevolutionTranslation(Axis axis, float positionX, float positionY);

	

public:

	void Update(float deltaTime) override;

	void SetRotation(float speed, Vec3 orientation);
	void SetRevolution(float speed, Axis axis, GameObject * gravityCenter, float radius, float elipticalProportion = 1.0f);
	void SetScale(float scale);
	void SetGravityCenter(GameObject * gravityCenter);
	void SetRotationTilt(float angle, Vec3 orientation = Vec3(0.0f, 1.0f, 0.0f));
	void addSatelite(CelestialBody * satelite);

	float GetRotationSpeed();


	CelestialBody(Mesh *mesh_, Shader *shader_, Texture *texture_);
	CelestialBody(Mesh *mesh_, Shader *shader_, const char texturePath[]);
	~CelestialBody();

};
#endif

