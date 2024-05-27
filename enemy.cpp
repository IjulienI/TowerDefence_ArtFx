#include "enemy.h"

Enemy::~Enemy() {
	position = { -1000,-1000 };
	gm->AddMoney(drop);
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
	
	DrawCircleLines(position.x, position.y, radius, RED);
}

void Enemy::SetPosition(const Vec2 position) {
	this->position = position;
}

Vec2 Enemy::GetPosition() {
	return position;
}

Vec2 Enemy::GetSize() {
	return size;
}

void Enemy::SetRadius() {
	if (size.x > size.y)
		radius = size.x / 2;
	else
		radius = size.y / 2;
}

float Enemy::GetRadius() {
	return radius;
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
	float targetRotation = atan2(direction.y, direction.x) * (180 / PI);

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

void Enemy::MakeDamage(float dt) {
	delay += 1 * dt;
	if (delay >= attackDelay) {
		gm->ApplyDamage(damage);
		delay = 0;
	}
}

void Enemy::ApplyDamage(const int amount) {
	health -= amount;
	if (health <= 0)
		dead = true;
	std::cout << health << std::endl;
}

void Enemy::SetLifeMultiplier(const int time) {
	this->health += (health / 0.25) * time;
}

bool Enemy::GetDeath() {
	return dead;
}

void Enemy::SetDeath(const bool status) {
	dead = status;
}

int Enemy::GetDrop() {
	return drop;
}

void Enemy::SetDropMultiplier(const int time) {
	this->drop *= time;
}


SmallEnemy::SmallEnemy(gameManager* gameManager) {
	texture = LoadTexture("textures/enemies/smallEnemy.png");
	size = { 25,15 };
	speed = 50;
	rotationSpeed = speed * 6;

	health = 15;
	damage = 50;
	drop = 100;

	attackDelay = 1;
	delay = attackDelay - 0.2;

	this->gm = gameManager;
	SetRadius();
}
MidEnemy::MidEnemy(gameManager* gameManager) {
	texture = LoadTexture("textures/enemies/midEnemy.png");
	size = { 35,25 };
	speed = 70;
	rotationSpeed = speed * 6;

	health = 25;
	damage = 100;
	drop = 200;

	attackDelay = 1.5;
	delay = attackDelay - 0.2;

	this->gm = gameManager;
	SetRadius();
}
BigEnemy::BigEnemy(gameManager* gameManager) {
	texture = LoadTexture("textures/enemies/bigEnemy.png");
	size = { 40,30 };
	speed = 75;
	rotationSpeed = speed * 6;

	health = 45;
	damage = 150;
	drop = 350;

	attackDelay = 2;
	delay = attackDelay - 0.2;

	this->gm = gameManager;
	SetRadius();
}
Boss::Boss(gameManager* gameManager) {
	texture = LoadTexture("textures/enemies/boss.png");
	size = { 60,45 };
	speed = 35;
	rotationSpeed = speed * 6;

	health = 500;
	damage = 350;
	drop = 2000;

	attackDelay = 3;
	delay = attackDelay - 0.2;

	this->gm = gameManager;
	SetRadius();
}