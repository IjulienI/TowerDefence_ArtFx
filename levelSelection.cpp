#include "levelSelection.h"

LevelSelection::LevelSelection() {
	this->line = 0;
	this->colonn = 1;
	this->levelTextures;
	Init();
}

LevelSelection::~LevelSelection() {
	for (int i = 0; i < levelTextures.size(); i++) {
		UnloadTexture(levelTextures[i]);
	}
}

void LevelSelection::Init() {
	std::string path = "textures/maps";	

	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (entry.path().extension() == ".png") {
			std::string filePath = entry.path().string();
			Texture2D texture = LoadTexture(filePath.c_str());
			levelTextures.push_back(texture);
			if (line < 4) {
				line++;
			} else colonn++;
		}
	}
}

void LevelSelection::Update(float dt) {
	int levelIndex = 0;
	for (int i = 0; i < line; i++) {
		if (GuiButton({ (float)(i * 266) + 10, 15,256,176 }, "")) {
			sceneManager->LoadMap(levelIndex);
		}
		levelIndex++;
	}
	if (colonn > 1) {
		for (int i = 0; i + 1 < colonn; i++) {
			if (GuiButton({ (float)(i * 266) + 10, 186 + 15,256,176 }, "")) {
				sceneManager->LoadMap(levelIndex);
			}
			levelIndex++;
		}
	}
}

void LevelSelection::Draw() {
	int levelIndex = 0;
	for (int i = 0; i < line; i++) {
		DrawTextureEx(levelTextures[levelIndex],{ (float)(i * 266) + 10, 15 },0,16,WHITE);
		levelIndex++;
	}
	if (colonn > 1) {
		for (int i = 0; i + 1 < colonn; i++) {
			DrawTextureEx(levelTextures[levelIndex], { (float)(i * 266) + 10, 186 + 15 }, 0, 16, WHITE);
			levelIndex++;
		}
	}
}