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



Scene2::Scene2() :
	camera(nullptr), meshPtr(nullptr), shaderPtr(nullptr) {}


Scene2::~Scene2() {}

bool Scene2::OnCreate()
{
	camera = new Camera();
	ModelScale = 0.6f;
	CameraRotation.loadIdentity();

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
	//Sun->addSatelite(Earth);
	SceneObjectList.push_back(Earth);

	CelestialBody * Moon;
	Moon = new CelestialBody(meshPtr, shaderPtr, "moon.jpg");
	Moon->SetRotation((Earth->GetRotationSpeed() / 27.0f) * TimeScale, Vec3(0.0f, 0.0f, 1.0f));
	Moon->SetRevolution((Earth->GetRotationSpeed() / 27.0f) * TimeScale, Z, Earth, 2.0f * ModelScale);
	Moon->SetScale(0.25f * ModelScale);
	//Earth->addSatelite(Moon);
	SceneObjectList.push_back(Moon);

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		if (SceneObjectList[i] == nullptr)
		{
			Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
			return false;
		}
	}
	LightSources.push_back(Light(Vec4(1.0, 1.0, 1.0, 0.0), 1.0f, Vec3(13.0f, 0.0f, 0.0f)));

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
		else if (sdlEvent.key.keysym.sym == SDLK_LCTRL)
		{
			CameraRotationFlag = true;
		}
		break;
	case SDL_EventType::SDL_KEYUP:
		if (sdlEvent.key.keysym.sym == SDLK_LCTRL)
		{
			CameraRotationFlag = false;
		}
	case SDL_EventType::SDL_MOUSEMOTION:
		if (CameraRotationFlag)
		{
			RotateCamera(CameraRotationZero, sdlEvent.motion.x, sdlEvent.motion.y, 0.1f);
		}
		else
		{
			
			CameraRotationZero.x = sdlEvent.motion.x;
			CameraRotationZero.y = sdlEvent.motion.y;
		}
		break;
	}
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

void Scene2::RotateCamera(Vec2 initialRotation, float xFinal, float yFinal, float radius)
{

	if (abs(initialRotation.x - xFinal) < 0.1f && abs(initialRotation.y - yFinal) < 0.1f) return;
	
	int xInitial = initialRotation.x;
	int yInitial = initialRotation.y;
	
	int zInitial, zFinal;
	
	if ((xInitial*xInitial) + (yInitial*yInitial) < radius*radius)
	{
		zInitial = sqrt(1 - (xInitial*xInitial) + (yInitial*yInitial));
	}
	else
	{
		zInitial = ((radius*radius)*0.5f) / ((xInitial*xInitial) + (yInitial*yInitial));
	}

	if ((xFinal*xFinal) + (yFinal*yFinal) < radius * radius)
	{
		zFinal = sqrt(1 - (xFinal*xFinal) + (yFinal*yFinal));
	}
	else
	{
		zFinal = ((radius*radius)*0.5f) / ((xFinal*xFinal) + (yFinal*yFinal));
	}

	Vec3 V1 = Vec3(xInitial, yInitial, zInitial);
	Vec3 V2 = Vec3(xFinal, yFinal, zFinal);
	
	V1 = VMath::normalize(V1);
	V2 = VMath::normalize(V2);

	Vec3 Normal = VMath::cross(V1, V2);
	float Angle = acos(VMath::dot(V1, V2));

	camera->SetRotation(cos(Angle / 2.0f) * 57.2958f, sin(Angle / 2.0f) * Normal);
}

void Scene2::Update(const float deltaTime_)
{
	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		dynamic_cast<CelestialBody*>(SceneObjectList[i])->Update(deltaTime_);
	}
}

void Scene2::Render() const
{
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	///Draw the Skybox
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	GLuint program = Skybox->GetShader()->getProgram();
	glUseProgram(program);
	glUniformMatrix4fv(Skybox->GetShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(Skybox->GetShader()->getUniformID("viewMatrix"), 1, GL_FALSE, (camera->getRotation()));
	glBindTexture(GL_TEXTURE_CUBE_MAP, Skybox->getTextureID());
	Skybox->CubeMesh->Render();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	//Skybox->Render(camera);

	/// Draw your scene here
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	program = SceneObjectList[0]->getShader()->getProgram();
	glUseProgram(program);

	for (int i = 0; i < SceneObjectList.size(); i++)
	{
		/// These pass the matricies and the light position to the GPU
		glUniformMatrix4fv(SceneObjectList[i]->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
		glUniformMatrix4fv(SceneObjectList[i]->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, (camera->getViewMatrix() * CameraRotation));
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