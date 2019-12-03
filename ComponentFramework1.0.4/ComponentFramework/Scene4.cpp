#include "Scene4.h"
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
#include "CubeMap.h"
#include "VMath.h"
#include "Trackball.h"
#include "CelestialBody.h"
#include "MMath.h"


Scene4::Scene4()
{
}


Scene4::~Scene4()
{
}

bool Scene4::OnCreate()
{
	camera = new Camera();
	SceneTrackball = new Trackball();

	//Create the Skybox
	std::vector<const char*> SkyboxTextures;
	SkyboxTextures.push_back("CN_Tower\\posx.jpg");
	SkyboxTextures.push_back("CN_Tower\\negx.jpg");
	SkyboxTextures.push_back("CN_Tower\\posy.jpg");
	SkyboxTextures.push_back("CN_Tower\\negy.jpg");
	SkyboxTextures.push_back("CN_Tower\\posz.jpg");
	SkyboxTextures.push_back("CN_Tower\\negz.jpg");

	Skybox = new CubeMap(SkyboxTextures);

	//Load Skull Model
	if (ObjLoader::loadOBJ("sphere.obj") == false)
	{
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("simpleReflectionVert.glsl", "simpleRefractionFrag.glsl");//Set shader to reflection shader

	//Create the Waterdrop Object
	Texture * WaterTexture = nullptr;
	GameObject * Waterdrop = new GameObject(meshPtr, shaderPtr, WaterTexture);
	Waterdrop->setModelMatrix(MMath::scale(0.01f, 0.01f, 0.01f));
	SceneObjectList.push_back(Waterdrop);

	LightSources.push_back(new Light(Vec4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, Vec3(0.0f, 0.0f, -20.0f), shaderPtr));
	return true;
}

void Scene4::OnDestroy()
{
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
		if (SceneObjectList[i]) delete SceneObjectList[i], SceneObjectList[i] = nullptr;
	}
}

void Scene4::HandleEvents(const SDL_Event & sdlEvent)
{
	switch (sdlEvent.type)
	{
	case SDL_EventType::SDL_KEYDOWN:
		if (sdlEvent.key.keysym.sym == SDLK_SPACE)
		{
			ResetCamera();
		}
		break;
	}

	SceneTrackball->HandleEvents(sdlEvent);
}

void Scene4::Update(const float deltaTime_)
{
	SceneObjectList[0]->setModelMatrix(MMath::translate(Vec3(0.0f, 0.0f, -10.0f)));

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		if (dynamic_cast<CelestialBody*>(SceneObjectList[i]))
		{
			dynamic_cast<CelestialBody*>(SceneObjectList[i])->Update(deltaTime_);
		}
		else
		{
			SceneObjectList[i]->Update(deltaTime_);
		}
	}

	if (SceneTrackball->IsTrackballTurning() && SceneTrackball->HasMoved)
	{
		camera->SetRotation(SceneTrackball->GetRotationMatrix() * camera->getRotation());
	}

	SceneObjectList[0]->setModelMatrix(MMath::scale(0.1f, 0.1f, 0.1f));

	SceneTrackball->HasMoved = false;
}

void Scene4::Render() const
{
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///Draw the Skybox
	Skybox->Render(camera);

	/// Draw your scene here
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		SceneObjectList[i]->Render(camera);
	}

	glUseProgram(0);
}

void Scene4::ResetCamera()
{
}