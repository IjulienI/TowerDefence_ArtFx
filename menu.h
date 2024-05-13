#pragma once
#include "scene.h"
#include "sceneManager.h"
#include <raylib.h>
#include "raygui.h"

class Menu : public Scene{
public:
	Menu();
	~Menu();

	void Init() override;
	void Update(float dt) override;
	void Draw() override;
private:
	Rectangle menuButton;
};