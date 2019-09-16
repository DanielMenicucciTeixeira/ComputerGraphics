#include <glew.h>
#include <iostream>
#include "Window.h"
#include "Debug.h"
#include "Scene0.h"
#include "Camera.h"
#include "GameObject.h"
#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "MMath.h"

Scene0::Scene0():
	camera(nullptr), gameObject(nullptr),meshPtr(nullptr),shaderPtr(nullptr),texturePtr(nullptr) {}

Scene0::~Scene0() {}

bool Scene0::OnCreate() {
	camera = new Camera();

	if (ObjLoader::loadOBJ("skull.obj") == false) {
		return false;
	}
	meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	shaderPtr = new Shader("phongVert.glsl", "phongFrag.glsl");
	texturePtr = new Texture();
	if (meshPtr == nullptr|| shaderPtr == nullptr || texturePtr == nullptr) {
		Debug::FatalError("Couldn't create game object assets", __FILE__, __LINE__);
		return false;
	}
	if (texturePtr->LoadImage("skull_texture.jpg") == false) {
		Debug::FatalError("Couldn't load texture", __FILE__, __LINE__);
		return false;
	}
	gameObject = new GameObject(meshPtr, shaderPtr, texturePtr);
	if (gameObject == nullptr) {
		Debug::FatalError("GameObject could not be created", __FILE__, __LINE__);
		return false;
	}

	//Creating each light and setting it's position
	LightSources.push_back(Light(Vec4(0.6, 0.0, 0.9, 0.0), 1.0f, Vec3(5.0, 5.0, 0.0)));
	LightSources.push_back(Light(Vec4(1.0, 0.6, 0.0, 0.0), 1.0f, Vec3(-5.0, 5.0, 0.0)));
	LightSources.push_back(Light(Vec4(0.8, 0.0, 0.6, 0.0), 1.0f, Vec3(0.0, -5.0, 0.0)));


	return true;
}

void Scene0::OnDestroy() {
	if(camera) delete camera, camera = nullptr;
	if(meshPtr) delete meshPtr, meshPtr = nullptr;
	if(texturePtr) delete texturePtr, texturePtr = nullptr;
	if(shaderPtr) delete shaderPtr, shaderPtr = nullptr;
	if(gameObject) delete gameObject, gameObject = nullptr;
}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene0::Update(const float deltaTime_) {
	gameObject->Update(deltaTime_);
	static float rotation = 0.0f;
	rotation += 0.5;
	gameObject->setModelMatrix(MMath::rotate(rotation, Vec3(0.0, 1.0, 0.0)));
}

void Scene0::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/// Draw your scene here
	GLuint program = gameObject->getShader()->getProgram();
	glUseProgram(program);

	/// These pass the matricies and the light position to the GPU
	glUniformMatrix4fv(gameObject->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(gameObject->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform1i(gameObject->getShader()->getUniformID("NumberOfLights"),LightSources.size());



	char Location[] = "lightPos[0]";//This parameter must be passed to find the adress of the firt variable of the array.
	for (int i = 0; i < LightSources.size(); i++)
	{
		//each variable beyond the first is located one unit after the prior varible, just like in the array, so this just parses through them, one by one, setting the Position values
		glUniform3fv(gameObject->getShader()->getUniformID("lightPos[0]") + i, 1, LightSources[i].Position);
		glUniform4fv(gameObject->getShader()->getUniformID("lightColour[0]") + i,1, LightSources[i].Colour);
		glUniform1f(gameObject->getShader()->getUniformID("lightColour[0]") + i, LightSources[i].Intensity);
	}

	gameObject->Render();

	glUseProgram(0);
}
