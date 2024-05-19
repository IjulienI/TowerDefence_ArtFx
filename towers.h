#pragma once

#include <vector>
#include "Vec2.h"
#include "raylib.h"
#include "enemy.h"

class Towers {
private:
	int targetDistance = 0;
	int damage = 0;
	int shootDelay = 0;

	float rotation = 0;

	Vec2 position = { 0,0 };

	Texture2D texture = LoadTexture("textures/base.png");

	std::vector<Enemy*> enemies;
public:
	Towers();
	Towers(std::vector<Enemy*> enemies);
	~Towers();

	void Update(float dt);
	void Draw();
	void SetEnemies(std::vector<Enemy*> enemies);
};

