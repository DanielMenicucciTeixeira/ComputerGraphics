#include "Scene1.h"
#include <glew.h>
#include <iostream>
#include "Window.h"
#include "Debug.h"
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
	ModelScale = 0.6f;

	if (ObjLoader::loadOBJ("sphere.obj") == false) 
	{
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");

	CelestialBody * Earth = new CelestialBody(meshPtr, shaderPtr, "earthclouds.jpg");
	Earth->SetRotation(360.0f * TimeScale, Vec3(0.0f, 0.0f, 1.0f));
	//Earth->SetRotationTilt(-23.0f);
	Earth->SetScale(ModelScale);
	SceneObjectList.push_back(Earth);

	CelestialBody * Moon;
	Moon = new CelestialBody(meshPtr, shaderPtr, "moon.jpg");
	Moon->SetRotation(Earth->GetRotationSpeed() / 27.0f, Vec3(0.0f, 0.0f, 1.0f));
	Moon->SetRevolution((Earth->GetRotationSpeed() / 27.0f), Z, Earth, 10*ModelScale);
	Moon->SetScale(ModelScale*0.5f);
	SceneObjectList.push_back(Moon);

	for(int i = 0; i < SceneObjectList.size(); i++)
	{
		if (SceneObjectList[i] == nullptr)
		{
			Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
			return false;
		}
	}
	LightSources.push_back(Light(Vec4(1.0, 1.0, 1.0, 0.0), 1.0f, Vec3(-100.0f, 0.0f, 0.0f)));


	return true;
}

void Scene1::OnDestroy() 
{
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
		if (SceneObjectList[i]) delete SceneObjectList[i], SceneObjectList[i]= nullptr;
	}
}

void Scene1::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene1::Update(const float deltaTime_) 
{
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		dynamic_cast<CelestialBody*>(SceneObjectList[i])->Update(deltaTime_);
	}
}

void Scene1::Render() const 
{
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Draw your scene here
	GLuint program = SceneObjectList[0]->getShader()->getProgram();
	glUseProgram(program);

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		/// These pass the matricies and the light position to the GPU
		glUniformMatrix4fv(SceneObjectList[i]->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
		glUniformMatrix4fv(SceneObjectList[i]->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
		glUniform1i(SceneObjectList[i]->getShader()->getUniformID("NumberOfLights"), LightSources.size());
	}

	char Location[] = "lightPos[0]";//This parameter must be passed to find the adress of the firt variable of the array.
	for (int i = 0; i < LightSources.size(); i++)
	{
		//each variable beyond the first is located one unit after the prior varible, just like in the array, so this just parses through them, one by one, setting the Position values
		glUniform3fv(SceneObjectList[0]->getShader()->getUniformID("lightPos[0]") + i, 1, LightSources[i].Position);
		glUniform4fv(SceneObjectList[0]->getShader()->getUniformID("lightColour[0]") + i, 1, LightSources[i].Colour);
		glUniform1f(SceneObjectList[0]->getShader()->getUniformID("lightColour[0]") + i, LightSources[i].Intensity);
	}

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		SceneObjectList[i]->Render();
	}

	glUseProgram(0);
}
