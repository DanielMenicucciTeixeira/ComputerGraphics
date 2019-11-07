#ifndef SCENE3_H
#define SCENE3_H

#include "Scene.h"
#include <vector>
#include "Light.h"


union SDL_Event;
class Camera;
class GameObject;
class Light;
class Mesh;
class Shader;
class Texture;
class Trackball;

class Scene3 : public Scene
{
private:
	Camera *camera;
	std::vector<Light*> LightSources;
	std::vector<GameObject*> SceneObjectList;
	Mesh *meshPtr;
	Shader *shaderPtr;

public:
	explicit Scene3();
	virtual ~Scene3();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;

	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;

	void ResetCamera();

};
#endif
