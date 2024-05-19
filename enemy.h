#pragma once

#include <raylib.h>
#include "Vec2.h"
#include <vector>
#include <math.h>
#include "gameManager.h"
#include <iostream>

class Enemy {
protected:
	Texture2D texture;
	Vec2 position;
	Vec2 size;
	std::vector<Vec2> path;

	float rotation;
	float speed;
	float rotationSpeed;

	int health;
	int damage;
	int drop;	

	int attackDelay;
	float delay;

	bool dead = false;

	gameManager* gm;
	
	virtual void MoveToward(const Vec2 target, float dt);
	virtual void UpdateRotation(const Vec2 direction, float dt);
	virtual void MakeDamage(float dt);

	virtual void IsDead();
public:
	virtual ~Enemy();

	virtual void Update(float dt);
	virtual void Draw();

	virtual void SetPosition(const Vec2 position);
	virtual Vec2 GetPosition();

	virtual void SetPath(std::vector<Vec2> path);

	virtual void ApplyDamage(const int amount);

	virtual bool GetDeath();
	virtual void SetDeath(const bool status);
};

class SmallEnemy : public Enemy {
public:
	SmallEnemy(gameManager* gameManager);
};

class MidEnemy : public Enemy {
public:
	MidEnemy(gameManager* gameManager);
};

class BigEnemy : public Enemy {
public:
	BigEnemy(gameManager* gameManager);
};

class Boss : public Enemy {
public:
	Boss(gameManager* gameManager);
};