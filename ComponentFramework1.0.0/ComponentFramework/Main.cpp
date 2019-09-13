#include "GameSceneManager.h"

int main(int argc, char* args[]) {
	GameSceneManager* gsm = new GameSceneManager();
	gsm->Init("Engine", 800, 600);
	gsm->Run();
	delete gsm;
	exit(0);
}