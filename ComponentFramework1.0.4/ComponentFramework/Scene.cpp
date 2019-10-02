#include "Scene.h"
#include <SDL.h>
#include "Camera.h"
#include "TrackBall.h"
#include "Window.h"

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
	Vec2 V1;
	Vec2 V0;


	V1.x = int(motion.motion.x);
	V1.y = int(motion.motion.y);

	V0.x = V1.x - int(motion.motion.xrel);
	V0.y = V1.y - int(motion.motion.xrel);

	TrackBall trackball = TrackBall(SceneWindow->GetHeight(), SceneWindow->GetWidth());
	Rotation rotation = trackball.GetRotation(V0, V1);
	//camera->Rotate(x * CameraRotationSpeed, Vec3(0.0f, 1.0f, 0.0f));
	camera->Rotate(rotation.Value * 57.2958, rotation.Orientation);
}

void Scene::SetWindow(Window * sceneWindow)
{
	SceneWindow = sceneWindow;
}
