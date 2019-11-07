#include "Scene3.h"
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


Scene3::Scene3()
{
}


Scene3::~Scene3()
{
}

bool Scene3::OnCreate()
{
	return false;
}

void Scene3::OnDestroy()
{
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
		if (SceneObjectList[i]) delete SceneObjectList[i], SceneObjectList[i] = nullptr;
	}
}

void Scene3::HandleEvents(const SDL_Event & sdlEvent)
{
}

void Scene3::Update(const float deltaTime_)
{
}

void Scene3::Render() const
{

}

void Scene3::ResetCamera()
{
}