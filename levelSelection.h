#pragma once
#include "scene.h"
#include "sceneManager.h"

#include "raygui.h"
#include "iostream"
#include "filesystem"
#include <vector>

class LevelSelection : public Scene {
public:
	LevelSelection();
	~LevelSelection();

	void Init() override;
	void Update(float dt) override;
	void Draw() override;
private:
	int line;
	int colonn;
	std::vector<Texture2D> levelTextures;
};

