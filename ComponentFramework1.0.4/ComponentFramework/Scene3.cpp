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
#include "CelestialBody.h"


Scene3::Scene3()
{
}


Scene3::~Scene3()
{
}

bool Scene3::OnCreate()
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
	if (ObjLoader::loadOBJ("skull.obj") == false)
	{
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("reflectionVert.glsl", "reflectionFrag.glsl");//Set shader to reflection shader

	//Create the Crystal Skull Object
	CelestialBody * CrystalSkull = new CelestialBody(meshPtr, shaderPtr, "skull_texture", Skybox, 1);
	CrystalSkull->SetRotation(100.0f, Vec3(0.0f, 1.0f, 0.0f));
	SceneObjectList.push_back(CrystalSkull);

	LightSources.push_back(new Light(Vec4(1.0f, 1.0f, 1.0f, 0.0f), 1.0f, Vec3(0.0f, 0.0f, 5.0f), shaderPtr));
	return true;
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

void Scene3::Update(const float deltaTime_)
{
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		dynamic_cast<CelestialBody*>(SceneObjectList[i])->Update(deltaTime_);
	}

	if (SceneTrackball->IsTrackballTurning() && SceneTrackball->HasMoved)
	{
		camera->SetRotation(SceneTrackball->GetRotationMatrix() * camera->getRotation());
	}

	SceneTrackball->HasMoved = false;
}

void Scene3::Render() const
{
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///Draw the Skybox
	Skybox->Render(camera);

	/// Draw your scene here
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	GLuint program = SceneObjectList[0]->getShader()->getProgram();
	glUseProgram(program);

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		/// These pass the matricies and the light position to the GPU
		glUniformMatrix4fv(SceneObjectList[i]->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
		glUniformMatrix4fv(SceneObjectList[i]->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, (camera->getViewMatrix()));
		glUniform1i(SceneObjectList[i]->getShader()->getUniformID("NumberOfLights"), LightSources.size());
	}

	if(LightSources.size() > 0) LightSources[0]->RenderLights(LightSources);

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		SceneObjectList[i]->Render();
	}

	glUseProgram(0);
}

void Scene3::ResetCamera()
{
}