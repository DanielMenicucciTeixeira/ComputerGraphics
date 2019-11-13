#include "GameObject.h"
#include <SDL_image.h>
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "Debug.h"
#include "CubeMap.h"
#include "Camera.h"

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

bool GameObject::LoadCube(std::vector<const char*>  cubeTextures)
{
	SDL_Surface *textureSurface = nullptr;
	int mode;

	glGenTextures(1, &enviroMapID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, enviroMapID);

	//Begin loading each of the CubesFaces, this is not in a loop due to the constante number of iterantions (6) and the fact that GL_TEXTURE_CUVE_MAP_* are frammer buffers, rather then enums,
	//and looping through them might compromise the use of this method in newer versions of OpenGL
	textureSurface = IMG_Load(cubeTextures[0]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	textureSurface = IMG_Load(cubeTextures[1]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	;
	textureSurface = IMG_Load(cubeTextures[2]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	;
	textureSurface = IMG_Load(cubeTextures[3]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	textureSurface = IMG_Load(cubeTextures[4]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);

	textureSurface = IMG_Load(cubeTextures[5]);
	if (textureSurface == nullptr) {
		return false;
	}
	mode = (textureSurface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, mode, textureSurface->w, textureSurface->h, 0, mode, GL_UNSIGNED_BYTE, textureSurface->pixels);
	SDL_FreeSurface(textureSurface);
	//End loading each cube face

	printf("All CubeMap Faces loaded successfully!\n");

	/// Wrapping and filtering options
	
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0); /// Unbind the textures
	HasEnviromap = true;
	return true;
}

GameObject::GameObject(Mesh * mesh_, Shader * shader_, const char texturePath[], CubeMap * enviroMap, GLfloat reflectionCoeficient)
{
	mesh = mesh_;
	shader = shader_;
	modelMatrixID = shader->getUniformID("modelMatrix");
	normalMatrixID = shader->getUniformID("normalMatrix");
	//reflectionCoeficientID = shader->getUniformID("reflectionCoeficient");
	//enviroMapID = shader->getUniformID("enviroMap");
	
	//ReflectionCoeficient = reflectionCoeficient;

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
		modelMatrix = modelMatrix * MMath::translate(direction * distance);
	}
	else
	{
		modelMatrix = modelMatrix * MMath::translate(direction);
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

void GameObject::Render(Camera * camera) const 
{

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	GLuint program = shader->getProgram();
	glUseProgram(program);


	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(shader->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(shader->getUniformID("viewMatrix"), 1, GL_FALSE, (camera->getViewMatrix()));
	glUniform3f(shader->getUniformID("cameraPosition") + 0, 1, GL_FALSE, camera->getPositionVector().x);
	glUniform3f(shader->getUniformID("cameraPosition") + 1, 1, GL_FALSE, camera->getPositionVector().y);
	glUniform3f(shader->getUniformID("cameraPosition") + 2, 1, GL_FALSE, camera->getPositionVector().z);

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
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}