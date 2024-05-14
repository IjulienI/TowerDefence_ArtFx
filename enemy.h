#pragma once

#include <raylib.h>
#include "Vec2.h"
#include <vector>
#include <math.h>

class Enemy {
private:
	Texture2D texture = LoadTexture("textures/base.png");
	Vec2 position = { 0,0 };
	Vec2 size = { 0,0 };
	std::vector<Vec2> path;
	float rotation = 0;
	float speed = 50;

	int health = 0;
	int damage = 0;
	int drop = 0;
public:
	Enemy();
	~Enemy();

	void Update(float dt);
	void Draw();

	void SetPosition(Vec2 position);
	Vec2 GetPosition();

	void SetPath(std::vector<Vec2> path);

	void MoveToward(Vec2 target, float dt);
	void UpdateRotation(Vec2 direction);
};

//class SmallEnemy : public Enemy {
//private:
//
//public:
//	SmallEnemy();
//};