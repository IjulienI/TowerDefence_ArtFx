#pragma once
#include "scene.h"
#include "sceneManager.h"

#include "constant.h"
#include "tile.h"
#include "vector"
#include "filesystem"

class Game : public Scene {
public:
	Game();
	Game(int index);
	~Game();

	void Init() override;
	void Update(float dt) override;
	void Draw() override;
private:
	void LoadTiles();

	Tile* map[16][11];

	std::vector<Tile*> obstacles;
	std::vector<Tile*> checkPoints;

	int mapIndex = 0;
};