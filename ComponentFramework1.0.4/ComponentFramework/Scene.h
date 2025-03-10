#ifndef SCENE_H
#define SCENE_H

union SDL_Event;
class CubeMap;

class Scene
{
protected:

	float Pi = 22 / 7;
	CubeMap* Skybox = nullptr;
	

public:
	explicit Scene() {}
	virtual ~Scene() {}

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() const  = 0 ;
	virtual void HandleEvents(const SDL_Event &sdlEvent) = 0;
	
};
#endif