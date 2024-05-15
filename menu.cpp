#include "menu.h"

Menu::Menu() {
	this->menuButton = { WINDOW_SIZE.x / 2 - GUI_BUTTON_SIZE.x / 2,WINDOW_SIZE.y / 2 + GUI_BUTTON_SIZE.y / 2,GUI_BUTTON_SIZE.x,GUI_BUTTON_SIZE.y };
}

Menu::~Menu() {
}

void Menu::Init() {
}

void Menu::Update(float dt) {
}

void Menu::Draw() {
	if (GuiButton(menuButton, "MENU")) {
		sceneManager->ChangeScene(Scenes::MAP_SELECTION);
	}
}