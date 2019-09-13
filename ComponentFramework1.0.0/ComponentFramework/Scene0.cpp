#include <glew.h>
#include <iostream>
#include "Window.h"
#include "Scene0.h"



Scene0::Scene0(){

}


Scene0::~Scene0() {}

bool Scene0::OnCreate() {
	std::cout << "Creating Scene 0" << std::endl;
	return true;
}

void Scene0::OnDestroy() {}

void Scene0::HandleEvents(const SDL_Event &sdlEvent) {}

void Scene0::Update(const float deltaTime_) {}

void Scene0::Render() const {
	/// Draw your scene here
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//SDL_GL_SwapWindow(windowPtr->getSDLWindow());
}
