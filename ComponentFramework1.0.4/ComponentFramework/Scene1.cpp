#include <glew.h>
#include <iostream>
#include "Window.h"
#include "Debug.h"
#include "Scene1.h"
#include "Camera.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"
#include "CelestialBody.h"



Scene1::Scene1():
camera(nullptr),  meshPtr(nullptr), shaderPtr(nullptr){}


Scene1::~Scene1() {}

bool Scene1::OnCreate() 
{
	camera = new Camera();

	if (ObjLoader::loadOBJ("sphere.obj") == false) 
	{
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");

	SceneObject Earth;
	Earth.texture = new Texture();
	const char EarthTexturepaht[] = "earthclouds.jpg";
	TexturePaths.push_back(EarthTexturepaht);
	Earth.gameObject = new CelestialBody(meshPtr, shaderPtr, Earth.texture);
	Earth.gameObject->SetRotation(0.5 * TimeScale, Vec3(0.0f, 0.0f, 1.0f));
	SceneObjectList.push_back(Earth);

	/*SceneObject Moon;
	Moon.texture = new Texture();
	const char MoonTexturepaht[16] = "moon.jpg";
	Earth.texturepath = *MoonTexturepaht;
	Moon.gameObject = new CelestialBody(meshPtr, shaderPtr, Moon.texture);
	Moon.gameObject->SetGravityCenter(Earth.gameObject);
	Moon.gameObject->SetRotation(Earth.gameObject->GetRotationSpeed() / 27.0f, Vec3(0.0f, 0.0f, 1.0f));
	Moon.gameObject->SetRevolution(Earth.gameObject->GetRotationSpeed() / 27.0f, Z);
	SceneObjectList.push_back(Moon);*/

	for(int i = 0; i < SceneObjectList.size(); i++)
	{
		if (meshPtr == nullptr || shaderPtr == nullptr || SceneObjectList[i].texture == nullptr)
		{
			Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
			return false;
		}
		if (SceneObjectList[i].texture->LoadImage(Paths) == false)
		{
			Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
			return false;
		}
		if (SceneObjectList[i].gameObject == nullptr)
		{
			Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
			return false;
		}
	}

	 /*
	//setting the Earth
	if (meshPtr == nullptr || shaderPtr == nullptr ||  == nullptr) 
	{
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}
	if (textureEarth->LoadImage("earthclouds.jpg") == false) 
	{
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	Earth = new GameObject(meshPtr, shaderPtr, textureEarth);
	if (Earth == nullptr) 
	{
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	//-------------------------------------------------------------------------------

	//setting the Moon
	if (meshPtr == nullptr || shaderPtr == nullptr || textureMoon == nullptr)
	{
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}
	if (textureMoon->LoadImage("moon.jpg") == false)
	{
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	Moon = new GameObject(meshPtr, shaderPtr, textureMoon);
	if (Moon == nullptr)
	{
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}
	//--------------------------------------------------------------------------------
	*/

	//Creating each light and setting it's position
	LightSources.push_back(Light(Vec4(1.0, 1.0, 1.0, 0.0), 1.0f, Vec3(-100.0f, 0.0f, 0.0f)));


	return true;
}

void Scene1::OnDestroy() 
{
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		if (SceneObjectList[i].texture) delete SceneObjectList[i].texture, SceneObjectList[i].texture = nullptr;
		if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
		if (SceneObjectList[i].gameObject) delete SceneObjectList[i].gameObject, SceneObjectList[i].gameObject = nullptr;
	}
}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene1::Update(const float deltaTime_) 
{
	//Earth.gameObject->Update(deltaTime_);
	//Moon->Update(deltaTime_);
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		SceneObjectList[i].gameObject->Update(deltaTime_);
	}
	/*
	Vec3 EarthScale = Vec3(1.0f) * ModelScale;
	Vec3 MoonScale = EarthScale * 0.25f;
	float moonTranslationRadius = 60.0f * ModelScale;
	EarthRotation += 0.5f * TimeScale;
	MoonRotation = EarthRotation / 27.0f;

	//Need to convert the MoonRotation from degrees to radians for the cos and sin methods
	float moonXPosition = (cos(MoonRotation * (Pi / 180)) * moonTranslationRadius) + Earth->GetPosition().x;//The cos of the radian is the cartisian coordinate for X with circle of radius 1, by multiplying it by the TranslationRadius and adding Earth's X Position we get the actual Moon's X Position
	float moonYPosition = (sin(MoonRotation * (Pi / 180)) * moonTranslationRadius) + Earth->GetPosition().y;//The sin of the radian is the cartisian coordinate for Y with circle of radius 1, by multiplying it by the TranslationRadius and adding Earth's Y Position we get the actual Moon's Y Position

	Earth->setModelMatrix(MMath::scale(EarthScale) * MMath::rotate(-90, Vec3(1.0, 0.0, 0.0)) * MMath::rotate(EarthRotation, Vec3(0.0, 0.0, 1.0)));
	Moon->setModelMatrix(MMath::scale(MoonScale) * MMath::rotate(-90, Vec3(1.0, 0.0, 0.0)) * MMath::translate(moonXPosition, moonYPosition, 0.0) * MMath::rotate(MoonRotation, Vec3(0.0, 0.0, 1.0)));//
	*/
}

void Scene1::Render() const 
{
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Draw your scene here
	GLuint program = SceneObjectList[0].gameObject->getShader()->getProgram();
	glUseProgram(program);

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		/// These pass the matricies and the light position to the GPU
		glUniformMatrix4fv(SceneObjectList[i].gameObject->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
		glUniformMatrix4fv(SceneObjectList[i].gameObject->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
		glUniform1i(SceneObjectList[i].gameObject->getShader()->getUniformID("NumberOfLights"), LightSources.size());
	}

	char Location[] = "lightPos[0]";//This parameter must be passed to find the adress of the firt variable of the array.
	for (int i = 0; i < LightSources.size(); i++)
	{
		//each variable beyond the first is located one unit after the prior varible, just like in the array, so this just parses through them, one by one, setting the Position values
		glUniform3fv(SceneObjectList[0].gameObject->getShader()->getUniformID("lightPos[0]") + i, 1, LightSources[i].Position);
		glUniform4fv(SceneObjectList[0].gameObject->getShader()->getUniformID("lightColour[0]") + i, 1, LightSources[i].Colour);
		glUniform1f(SceneObjectList[0].gameObject->getShader()->getUniformID("lightColour[0]") + i, LightSources[i].Intensity);
	}

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		SceneObjectList[i].gameObject->Render();
	}

	glUseProgram(0);
}


/*void Scene1::HandleEvents(const SDL_Event &sdlEvent) 
{
}

void Scene1::Update(const float deltaTime_) 
{
}

void Scene1::Render() const 
{
}*/
