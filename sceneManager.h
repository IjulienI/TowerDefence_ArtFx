#pragma once
#include "scene.h"
#include "menu.h"
#include "game.h"
#include "levelSelection.h"

enum class Scenes {
	MENU,
	GAME,
	MAP_SELECTION
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