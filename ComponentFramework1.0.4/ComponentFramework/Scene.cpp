#include "Scene.h"
#include <SDL.h>
#include "Camera.h"

Scene::~Scene()
{
}

void Scene::OnDestroy()
{
	delete(Skybox); Skybox = nullptr;
}

void Scene::HandleEvents(const SDL_Event & sdlEvent)
{
	int x = 0;
	switch (sdlEvent.type)
	{
	case SDL_EventType::SDL_KEYDOWN:
		if (sdlEvent.key.keysym.sym == SDLK_1 || sdlEvent.key.keysym.sym == SDLK_2 || sdlEvent.key.keysym.sym == SDLK_3 || sdlEvent.key.keysym.sym == SDLK_4)
		{
			ToggleCamera(MainCamera, sdlEvent);
		}
		break;

	case SDL_EventType::SDL_MOUSEMOTION:
		MoveCamera(MainCamera, sdlEvent);
		break;

	default:
		break;
	}
}

void Scene::ToggleCamera(Camera * camera, SDL_Event key)
{
	Vec3 X = Vec3(1.0f, 0.0f, 0.0f);
	Vec3 Y= Vec3(0.0f, 1.0f, 0.0f);
	Vec3 Z = Vec3(0.0f, 0.0f, 1.0f);

	switch (key.key.keysym.sym)
	{
	case SDLK_1:
		camera->SetRotaion(0, Z);
		break;
	case SDLK_2:
		camera->SetRotaion(90, Y);
		break;
	case SDLK_3:
		camera->SetRotaion(90, Z);
		break;
	case SDLK_4:
		camera->SetRotaion(90, X);
		break;
	default:
		break;
	}
}

void Scene::MoveCamera(Camera * camera, SDL_Event motion)
{
	int x = motion.motion.xrel;
	int y = motion.motion.yrel;

	//camera->Rotate(x * CameraRotationSpeed, Vec3(0.0f, 1.0f, 0.0f));
	//camera->Rotate(y * CameraRotationSpeed, Vec3(1.0f, 0.0f,  0.0f));
}
