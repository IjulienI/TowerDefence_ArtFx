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

	Tile* map[16][11];

	std::vector<Vec2> waypoints;
	std::vector<Enemy*> enemies;
	std::vector<Towers*> towers;

	Vec2 start;
	gameManager gm;

	void CleanPath(std::vector<Vec2>& waypoints);
	Tile* GetTileAtLocation(Vec2 location);

	int mapIndex = 0;
};