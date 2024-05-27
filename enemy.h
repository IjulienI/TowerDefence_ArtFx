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
	float radius;

	float health;
	int damage;
	int drop;	

	int attackDelay;
	float delay;

	bool dead = false;

	gameManager* gm;
	
	virtual void MoveToward(const Vec2 target, float dt);
	virtual void UpdateRotation(const Vec2 direction, float dt);
	virtual void MakeDamage(float dt);
public:
	virtual ~Enemy();

	virtual void Update(float dt);
	virtual void Draw();

	virtual void SetPosition(const Vec2 position);
	virtual Vec2 GetPosition();
	virtual Vec2 GetSize();

	virtual void SetPath(std::vector<Vec2> path);

	virtual void SetRadius();
	virtual float GetRadius();

	virtual void ApplyDamage(const int amount);
	virtual void SetLifeMultiplier(const int time);

	virtual bool GetDeath();
	virtual void SetDeath(const bool status);

	virtual int GetDrop();
	virtual void SetDropMultiplier(const int time);
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