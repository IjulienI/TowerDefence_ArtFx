#pragma once

#include <vector>
#include "Vec2.h"
#include "raylib.h"
#include "enemy.h"
#include "ball.h"

class Towers {
private:
	int targetDistance = 0;
	int damage = 1;
	float shootDelay = 0.4;
	float delay = 0;

	int range = 150;

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
	bool CanShoot(float dt);
	void Draw();
	void SetEnemies(std::vector<Enemy*> enemies);

	Vec2 GetPosition();
	float GetRotation();

	int GetDamage();

	void SetPosition(Vec2 position);
};

