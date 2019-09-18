#ifndef SCENE1_H
#define SCENE1_H
#include "Scene.h"
#include "Vector.h"
#include "Light.h"
#include <string>
#include <vector>

/// Forward declarations 
union SDL_Event;
class Camera;
class GameObject;
class CelestialBody;
class Mesh;
class Shader;
class Texture;

struct SceneObject
{
	CelestialBody * gameObject = nullptr;
	Texture * texture = nullptr;
};

class Scene1 : public Scene 
{
private:
	Camera *camera;
	std::vector<Light> LightSources;
	std::vector<SceneObject> SceneObjectList;
	std::vector<const char[]> TexturePaths;
	std::vector<*untyped> Paths;
	Mesh *meshPtr;
	Shader *shaderPtr;

	float EarthRotation = 0.0f;
	float MoonRotation = 0.0f;

	float ModelScale = 1.0f;
	float TimeScale = 1.0f;

public:
	explicit Scene1();
	virtual ~Scene1();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime_) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event &sdlEvent) override;
};


#endif // !SCENE1_H