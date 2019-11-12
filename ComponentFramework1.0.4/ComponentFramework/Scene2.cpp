#include "Scene2.h"
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
#include "Light.h"



Scene2::Scene2() :
	camera(nullptr), meshPtr(nullptr), shaderPtr(nullptr) {}


Scene2::~Scene2() {}

bool Scene2::OnCreate()
{
	camera = new Camera();
	ModelScale = 0.6f;
	SceneTrackball = new Trackball();

	if (ObjLoader::loadOBJ("sphere.obj") == false)
	{
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("textureVert.glsl", "textureFrag.glsl");

	CelestialBody * Sun = new CelestialBody(meshPtr, shaderPtr, "yellow.jpg");
	Sun->SetRotation(0.0f, Vec3(0.0f, 0.0f, 1.0f));
	Sun->SetScale(2.0f * ModelScale);
	SceneObjectList.push_back(Sun);

	CelestialBody * Earth = new CelestialBody(meshPtr, shaderPtr, "earthclouds.jpg");
	Earth->SetRotation(360.0f * TimeScale, Vec3(0.0f, 0.0f, 1.0f));
	Earth->SetRotationTilt(23.0f);
	Earth->SetRevolution(((Earth->GetRotationSpeed()/365.0f)  * TimeScale), Z, Sun, 9.0f * ModelScale, 0.5f);
	Earth->SetScale(1.0f * ModelScale);
	SceneObjectList.push_back(Earth);

	CelestialBody * Moon;
	Moon = new CelestialBody(meshPtr, shaderPtr, "moon.jpg");
	Moon->SetRotation((Earth->GetRotationSpeed() / 27.0f) * TimeScale, Vec3(0.0f, 0.0f, 1.0f));
	Moon->SetRevolution((Earth->GetRotationSpeed() / 27.0f) * TimeScale, Z, Earth, 2.0f * ModelScale);
	Moon->SetScale(0.25f * ModelScale);
	SceneObjectList.push_back(Moon);

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		if (SceneObjectList[i] == nullptr)
		{
			Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
			return false;
		}
	}

	LightSources.push_back(new Light(Vec4(1.0, 0.5, 0.5, 1.0), 1.0f, Vec3(-2000.0f, 2000.0f, 0.0f), shaderPtr));
	LightSources.push_back(new Light(Vec4(0.5, 0.5, 1.0, 0.0), 0.3f, Vec3(2000.0f, -2000.0f, 0.0f), shaderPtr));

	std::vector<const char*> SkyboxTextures;
	SkyboxTextures.push_back("CN_Tower\\posx.jpg");
	SkyboxTextures.push_back("CN_Tower\\negx.jpg");
	SkyboxTextures.push_back("CN_Tower\\posy.jpg");
	SkyboxTextures.push_back("CN_Tower\\negy.jpg");
	SkyboxTextures.push_back("CN_Tower\\posz.jpg");
	SkyboxTextures.push_back("CN_Tower\\negz.jpg");

	Skybox = new CubeMap(SkyboxTextures);


	return true;
}

void Scene2::ToggleCamera()
{
	if (!CameraState)
	{
		camera->SetRotation(45, Vec3(0.0f, 1.0f, 0.0f));
	}
	else camera->SetRotation(0.0f, Vec3(1.0f, 0.0f, 0.0f));

	CameraState = !CameraState;
}



void Scene2::OnDestroy()
{
	if (camera) delete camera, camera = nullptr;
	if (meshPtr) delete meshPtr, meshPtr = nullptr;
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		if (shaderPtr) delete shaderPtr, shaderPtr = nullptr;
		if (SceneObjectList[i]) delete SceneObjectList[i], SceneObjectList[i] = nullptr;
	}
}

void Scene2::HandleEvents(const SDL_Event &sdlEvent)
{
	switch (sdlEvent.type)
	{
	case SDL_EventType::SDL_KEYDOWN:
		if (sdlEvent.key.keysym.sym == SDLK_SPACE)
		{
			ToggleCamera();
		}
		break;
	}

	SceneTrackball->HandleEvents(sdlEvent);
}

void Scene2::Update(const float deltaTime_)
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

void Scene2::Render() const
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

	LightSources[0]->RenderLights(LightSources);

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		SceneObjectList[i]->Render();
	}

	glUseProgram(0);
}