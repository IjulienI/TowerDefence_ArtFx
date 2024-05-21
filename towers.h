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

	int range = 15;

	float rotation = 0;

	Vec2 position = { 0,0 };
	Vec2 size = { 25,20 };

	Texture2D turret = LoadTexture("textures/towers/weapon.png");

	std::vector<Enemy*> enemies;
	Enemy* nearestEnemy = nullptr;

	Enemy* GetNearestEnemy(std::vector<Enemy*> enemies);
	void SetRotation();
public:
	Towers();
	Towers(std::vector<Enemy*> enemies);
	~Towers();

	void Update(float dt);
	void Draw();
	void SetEnemies(std::vector<Enemy*> enemies);

	void SetPosition(Vec2 position);
};

