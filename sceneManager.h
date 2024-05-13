#pragma once
#include "scene.h"
#include "menu.h"
#include "game.h"

enum Scenes {
	MENU,
	GAME
};

class SceneManager {
public:
	SceneManager();
	~SceneManager();

	void Update(float dt);
	void Draw();

	void ChangeScene(Scenes newScene);
	void LoadMap(int index);
private:
	Scene* currentScene;
	void Init();	
};
extern SceneManager* sceneManager;