#pragma once
#include "scene.h"
#include "sceneManager.h"

#include "constant.h"
#include "tile.h"
#include "towers.h"
#include "vector"
#include "enemy.h"
#include "filesystem"
#include <algorithm>
#include "gameManager.h"
#include <iostream>
#include "ball.h"

class Game : public Scene {
public:
	Game();
	Game(int index);
	~Game();

	void Init() override;
	void Update(float dt) override;
	void Draw() override;
private:
	void LoadMap();

	Texture2D road = LoadTexture("textures/road.png");
	Texture2D grass = LoadTexture("textures/grass.png");
	Texture2D finish = LoadTexture("textures/finish.png");
	Texture2D turretBase = LoadTexture("textures/towers/base.png");

	Tile* map[16][11];
	Tile* mouseOn;

	std::vector<Vec2> waypoints;
	std::vector<Enemy*> enemies;
	std::vector<Towers*> towers;
	std::vector<Ball*> balls;

	Vec2 start;
	Vec2 mousePos;
	gameManager gm;

	bool displayPrice;

	void CleanPath(std::vector<Vec2>& waypoints);
	Tile* GetTileAtLocation(Vec2 location);
	void MouseSystem();
	void Inputs();

	int mapIndex = 0;
};