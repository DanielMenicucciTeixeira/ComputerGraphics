#include "GameObject.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "CubeMap.h"

GameObject::GameObject(Vec3 position, Shader * _shader)
{
	Position = position;
	shader = _shader;
}

GameObject::GameObject(Mesh *mesh_, Shader *shader_, Texture *texture_):
	mesh(nullptr), shader(nullptr), texture(nullptr) {
	
	mesh = mesh_;
	shader = shader_;
	texture = texture_;
	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
	//enviroMapID = shader->getUniformID("enviroMap");
}

GameObject::GameObject(Mesh * mesh_, Shader * shader_, const char texturePath[], CubeMap * enviroMap, GLfloat reflectionCoeficient)
{
	mesh = mesh_;
	shader = shader_;
	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
	//reflectionCoeficientID = shader->getUniformID("reflectionCoeficient");
	//enviroMapID = shader->getUniformID("enviroMap");
	
	ReflectionCoeficient = reflectionCoeficient;

	EnviroMap = enviroMap;

	bool BugFound = false;

	if (mesh == nullptr || shader == nullptr)
	{
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		BugFound = true;
	}

	texture = new Texture();
	if (texture == nullptr || texture->LoadImage(texturePath) == false)
	{
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		BugFound = true;
	}

	BaseMatrix = RotationMatrix = PositionMatrix = modelMatrix;
}

GameObject::~GameObject() {}

void GameObject::Update(float deltaTime_) {}

void GameObject::addRotatation(float angle, Vec3 orientation)
{
	RotationMatrix = MMath::rotate(angle, orientation) * RotationMatrix;
}

void GameObject::addTranslation(Vec3 direction, float distance, bool useDistance)
{
	if (useDistance)
	{
		direction = direction / sqrt(direction.x*direction.x + direction.y*direction.y + direction.z*direction.z);
		PositionMatrix = PositionMatrix = PositionMatrix * MMath::translate(direction * distance);
	}
	else
	{
		PositionMatrix = PositionMatrix * MMath::translate(direction);
	}
}

void GameObject::SetOriginalTransform(Vec3 position, float angle, Vec3 rotation, Vec3 scale)
{
	BaseMatrix = MMath::translate(position) * MMath::rotate(angle, rotation) * MMath::scale(scale);
}

Vec3 GameObject::GetPosition()
{
	return Vec3(modelMatrix[13], modelMatrix[14], modelMatrix[15]);
	//return Position;
}

void GameObject::SetTexture(Texture * TextureToSet)
{
	texture = TextureToSet;
}

void GameObject::Render() const {
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

	mesh->Render();

	/// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);
}