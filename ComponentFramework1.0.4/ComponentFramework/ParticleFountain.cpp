#include "ParticleFountain.h"
#include <SDL_image.h>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "CubeMap.h"
#include "Camera.h"
#include "VMath.h"
#include <cstdlib>



ParticleFountain::ParticleFountain(Mesh *mesh_, Shader *shader_, const char texturePath[], CubeMap * skybox) : GameObject(mesh_, shader_, texturePath)
{
	for (int i = 0; i < 200; i++)
	{
		DirectionArray[i] = GetParticleDirection();
	}

	EnviroMap = skybox;
}


ParticleFountain::~ParticleFountain()
{
}

void ParticleFountain::RenderParticles(Camera * camera)
{
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	GLuint program = shader->getProgram();
	glUseProgram(program);


	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(shader->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(shader->getUniformID("viewMatrix"), 1, GL_FALSE, (camera->getViewMatrix()));
	glUniformMatrix4fv(shader->getUniformID("cameraPosition"), 1, GL_FALSE, camera->getPosition());
	//glUniform1f(shader->getUniformID("time"), deltaTime);

	Matrix3 normalMatrix = modelMatrix;
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, modelMatrix);
	glUniformMatrix3fv(normalMatrixID, 1, GL_FALSE, normalMatrix);
	//glUniform1f(reflectionCoeficientID, ReflectionCoeficient);

	if (texture)
	{
		glBindTexture(GL_TEXTURE_2D, texture->getTextureID());
	}
	if (EnviroMap != nullptr)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, EnviroMap->getTextureID());
	}

	
	glUniform1f(shader->getUniformID("time"), ParticleTime);
	glUniform1f(shader->getUniformID("speed"), ParticleSpeed);
	glUniform1f(shader->getUniformID("gravity"), Gravity);
	glUniform1f(shader->getUniformID("airDrag"), AirDrag);
	glUniform1f(shader->getUniformID("lifeSpan"), ParticleLifeSpan);
	glUniform1f(shader->getUniformID("deltaTime"), DeltaTime);
	glUniform1i(shader->getUniformID("verticalInstances"), VerticalInstances);
	glUniform1i(shader->getUniformID("horizontalInstances"), HorizontalInstances);


	for (int i = 0; i < HorizontalInstances; i++)
	{
		glUniform3fv(shader->getUniformID("directionArray[0]") + i, 1, DirectionArray[i]);
	}


	glBindVertexArray(mesh->GetVAO());
	glDrawArraysInstanced(mesh->GetDrawMode(), 0, mesh->GetVertices().size(), HorizontalInstances * VerticalInstances);
	glBindVertexArray(0); // Disable the VAO

	/// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void ParticleFountain::Update(float deltaTime)
{
	DeltaTime = deltaTime;
	Time += deltaTime;
	while (Time - TimeCycle * ParticleLifeSpan > ParticleLifeSpan) TimeCycle++;
	ParticleTime = Time - TimeCycle * ParticleLifeSpan;
}

float ParticleFountain::GausianRandom(int stability, bool includeNegative)
{
	float result = 0;

	if (includeNegative) for (int i = 0; i < stability; i++)
	{
		result += float(rand() % 20001) / 10000.0f;
		result -= 1;
	}
	else for (int i = 0; i < stability; i++)
	{
		result += float(rand() % 10001) / 10000.0f;
	}

	result = result / float(stability);

	return result;
}

Vec3 ParticleFountain::GetParticleMovement(Vec3 direction)
{
	return direction * ParticleSpeed * ParticleTime + Vec3(0, -1, 0) * Gravity * ParticleTime * ParticleTime * 0.5f;
}

Vec3 ParticleFountain::GetParticleDirection()
{
	//return VMath::rotate(Vec3(0.0f, 1.0f, 0.0f), AngularDiviantion * (GausianRandom(100, true)), Vec3(GausianRandom(1, true), 1, GausianRandom(1, true)));
	return VMath::rotate(VMath::normalize(Vec3((GausianRandom(1, true)), 0, (GausianRandom(1, true)))), AngularDiviantion * (GausianRandom(10)), Vec3(0.0f, 1.0f, 0.0f));
}


