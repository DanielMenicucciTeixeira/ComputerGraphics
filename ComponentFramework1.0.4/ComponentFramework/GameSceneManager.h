#ifndef GAMESCENEMANAGER_H
#define GAMESCENEMANAGER_H

#include <string>

enum SCENE_NUMBER
{
	SCENE0 = 0,
	SCENE1 = 1,
	SCENE2 = 2,
	SCENE3 = 3
};

class GameSceneManager  
{
public:
	
	GameSceneManager();
	~GameSceneManager();
	void Run();
	bool Init(std::string name_, int width_, int height_, SCENE_NUMBER sceneToRun, std::string SkyboxTextures[6] = NULL);
	void HandleEvents();
	
	
private:

	class Scene* currentScene;
	class Timer* timer;
	class Window* window;

	unsigned int fps;
	bool isRunning;
	Scene* BuildScene(SCENE_NUMBER scene_);
};


#endif // !GAMESCENEMANAGER_H