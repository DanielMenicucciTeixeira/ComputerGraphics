#pragma once
#include "GameObject.h"
class ParticleFountain :
	public GameObject
{
public:
	ParticleFountain(Mesh *mesh_, Shader *shader_, const char texturePath[], CubeMap * skybox);
	~ParticleFountain();

	void RenderParticles(Camera * camera);
	void Update(float deltaTime) override;

	float GausianRandom(int stability, bool includeNegative = false);
	
protected:
	int HorizontalInstances = 200;
	int VerticalInstances = 50;
	float ParticleSpeed = 30.0f;
	float AirDrag = 100.0f;
	float ParticleLifeSpan = 10.0f;
	float Gravity = 10.0f;
	float AngularDiviantion = 10.0f;
	float Time = 0;
	float DeltaTime;
	float ParticleTime = 0;
	int TimeCycle = 0;

	Vec3 DirectionArray[500];

	Vec3 GetParticleMovement(Vec3 direction);
	Vec3 GetParticleDirection();
};

