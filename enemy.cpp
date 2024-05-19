#include "enemy.h"

Enemy::~Enemy() {
	gm->AddMoney(drop);
	UnloadTexture(texture);
	std::cout << "Enemy Destroy" << std::endl;
}

void Enemy::Update(float dt) {
	if (path.empty()) {
		MakeDamage(dt);
		return;
	}

	Vec2 targetPos = path.front();

	MoveToward(targetPos, dt);
	if (abs(position.x - targetPos.x) < 25.0f && abs(position.y - targetPos.y) < 25.0f)
		path.erase(path.begin());	
}

void Enemy::Draw() {
	Rectangle enemy = { position.x,position.y,size.x,size.y };

	DrawTexturePro(texture, { 0,0,(float)texture.width,(float)texture.height }, enemy, { size.x / 2,size.y / 2 }, rotation, WHITE);
}

void Enemy::SetPosition(const Vec2 position) {
	this->position = position;
}

Vec2 Enemy::GetPosition() {
	return position;
}

void Enemy::SetPath(std::vector<Vec2> path) {
	this->path = path;
}

void Enemy::MoveToward(const Vec2 target, float dt) {
	Vec2 forward = target - position;

	float distance = sqrt(forward.x * forward.x + forward.y * forward.y);

	if (distance != 0) {
		forward /= distance;
		position += forward * speed * dt;
	}
	UpdateRotation(forward, dt);
}

void Enemy::UpdateRotation(const Vec2 direction, float dt) {
	float targetRotation = atan2(direction.y, direction.x) * (180/PI);

	float difference = targetRotation - rotation;

	if (difference > 180) difference -= 360;
	else if (difference < -180) difference += 360;

	if (difference > 0) 
		rotation += rotationSpeed * dt;
	else if (difference < 0) 
		rotation -= rotationSpeed * dt;

	if (abs(difference) < 10)
		rotation = targetRotation;
}

void Enemy::IsDead(){
	if (health <= 0)
		dead = true;
}

void Enemy::MakeDamage(float dt) {
	delay += 1 * dt;
	if (delay >= attackDelay) {
		gm->ApplyDamage(damage);
		delay = 0;
	}
}

void Enemy::ApplyDamage(const int amount) {
	health -= amount;
}

bool Enemy::GetDeath() {
	return dead;
}

void Enemy::SetDeath(const bool status) {
	dead = status;
}


SmallEnemy::SmallEnemy(gameManager* gameManager) {
	texture = LoadTexture("textures/enemies/smallEnemy.png");
	size = { 25,15 };
	speed = 50;
	rotationSpeed = speed * 6;

	health = 15;
	damage = 50;
	drop = 15;

	attackDelay = 1;
	delay = attackDelay - 0.2;

	this->gm = gameManager;
}
MidEnemy::MidEnemy(gameManager* gameManager) {
	texture = LoadTexture("textures/enemies/midEnemy.png");
	size = { 35,25 };
	speed = 70;
	rotationSpeed = speed * 6;

	health = 25;
	damage = 100;
	drop = 50;

	attackDelay = 1.5;
	delay = attackDelay - 0.2;

	this->gm = gameManager;
}
BigEnemy::BigEnemy(gameManager* gameManager) {
	texture = LoadTexture("textures/enemies/bigEnemy.png");
	size = { 40,30 };
	speed = 75;
	rotationSpeed = speed * 6;

	health = 45;
	damage = 150;
	drop = 100;

	attackDelay = 2;
	delay = attackDelay - 0.2;

	this->gm = gameManager;
}
Boss::Boss(gameManager* gameManager) {
	texture = LoadTexture("textures/enemies/boss.png");
	size = { 60,45 };
	speed = 150;
	rotationSpeed = speed * 6;

	health = 250;
	damage = 350;
	drop = 250;

	attackDelay = 3;
	delay = attackDelay - 0.2;

	this->gm = gameManager;
}