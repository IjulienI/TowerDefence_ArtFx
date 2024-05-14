#pragma once
#include "scene.h"
#include "sceneManager.h"

#include "constant.h"
#include "tile.h"
#include "vector"
#include "enemy.h"
#include "filesystem"
#include <algorithm>

class Game : public Scene {
public:
	Game();
	Game(int index);
	~Game();

	void Init() override;
	void Update(float dt) override;
	void Draw() override;
private:
	void Load();

	Tile* map[16][11];

	std::vector<Tile*> obstacles;
	std::vector<Tile*> checkPoints;
	std::vector<Vec2> waypoints;
	std::vector<Enemy*> enemies;

	void AlignPath(std::vector<Vec2>& waypoints);

	int mapIndex = 0;
};