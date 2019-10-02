#ifndef SCENE_H
#define SCENE_H

union SDL_Event;
class CubeMap;
class Camera;
class Window;

class Scene
{
protected:

	Camera *camera;
	float Pi = 22 / 7;
	CubeMap* Skybox = nullptr;
	Camera * MainCamera = nullptr;
	float CameraRotationSpeed = 0.5f;

public:
	explicit Scene() {}
	virtual ~Scene();

	virtual bool OnCreate() = 0;
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() const  = 0 ;
	virtual void HandleEvents(const SDL_Event &sdlEvent);
	virtual void ToggleCamera(Camera * camera, SDL_Event key);
	void MoveCamera(Camera * camera, SDL_Event motion);
};
#endif