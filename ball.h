#ifndef BALL_H
#define BALL_H

#include <raylib.h>
#include <vector>
#include "constant.h"
#include "gameManager.h"
#include "enemy.h"

class Ball {
private:
	Vec2 position = { 0,0 };
	float speed = 450;

	int radius = 5;
	int damage = 0;

	float rotation = 0;
	Color color = WHITE;

	bool needToBeDestroy = false;

	void WallCollision();
	void Movement(float dt);
public:
	Ball();
	~Ball();
	void Update(float dt);
	void Draw();

	void SetDamage(const int damage);
	int GetDamage();

	void SetPositionAndRotation(const Vec2 position,const float rotation);

	bool DetectCollision(Enemy* enemy);

	bool GetDeath();
};

#endif