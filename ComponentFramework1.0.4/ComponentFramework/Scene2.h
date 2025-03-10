#ifndef SCENE2_H
#define SCENE2_H

#include "Scene.h"
#include <vector>

/// Forward declarations 
union SDL_Event;
class Camera;
class GameObject;
class CelestialBody;
class Mesh;
class Shader;
class Texture;
class Trackball;
class Light;

class Scene2 : public Scene
{
	private:
		Camera *camera;
		std::vector<Light*> LightSources;
		std::vector<GameObject*> SceneObjectList;
		Mesh *meshPtr;
		Shader *shaderPtr;

		float EarthRotation = 0.0f;
		float MoonRotation = 0.0f;

		float ModelScale = 1.0f;
		float TimeScale = 1.0f;

		bool CameraState = false;

		Trackball * SceneTrackball = nullptr;

	public:
		explicit Scene2();
		virtual ~Scene2();

		virtual bool OnCreate() override;
		virtual void OnDestroy() override;
		virtual void Update(const float deltaTime_) override;
		virtual void Render() const override;
		virtual void HandleEvents(const SDL_Event &sdlEvent) override;
		
		void ToggleCamera();
};
#endif

