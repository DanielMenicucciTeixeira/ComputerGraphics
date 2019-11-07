#ifndef SCENE2_H
#define SCENE2_H

#include "Scene.h"
#include "Vector.h"
#include "Light.h"
#include <string>
#include <vector>
#include <SDL_ttf.h>

/// Forward declarations 
union SDL_Event;
class Camera;
class GameObject;
class CelestialBody;
class Mesh;
class Shader;
class Texture;

class Scene2 : public Scene
{
	private:
		Camera *camera;
		std::vector<Light> LightSources;
		std::vector<GameObject*> SceneObjectList;
		Mesh *meshPtr;
		Shader *shaderPtr;

		float EarthRotation = 0.0f;
		float MoonRotation = 0.0f;

		float ModelScale = 1.0f;
		float TimeScale = 1.0f;

		Matrix4 CameraRotation;
		bool CameraState = false;

		bool CameraRotationFlag = false;
		Vec2 CameraRotationZero;

	public:
		explicit Scene2();
		virtual ~Scene2();

		virtual bool OnCreate() override;
		virtual void OnDestroy() override;
		virtual void Update(const float deltaTime_) override;
		virtual void Render() const override;
		virtual void HandleEvents(const SDL_Event &sdlEvent) override;
		
		void ToggleCamera();
		void RotateCamera(Vec2 initalRotation, float xFinal, float yFinal, float radius);
};
#endif

