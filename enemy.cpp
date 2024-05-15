#include "enemy.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
	UnloadTexture(texture);
}

void Enemy::Update(float dt) {
	if (path.empty())
		return;
	Vec2 targetPos = path.front();
	MoveToward(targetPos, dt);
	if (abs(position.x - targetPos.x) < 1.0f && abs(position.y - targetPos.y) < 1.0f)
		path.erase(path.begin());
}

void Enemy::Draw() {
	Rectangle enemy = { position.x,position.y,30,30 };
	DrawTexturePro(texture, { 0,0,(float)texture.width,(float)texture.height }, enemy, { 15,15 }, rotation, WHITE);
}

void Enemy::SetPosition(Vec2 position) {
	this->position = position;
}

Vec2 Enemy::GetPosition() {
	return position;
}

void Enemy::SetPath(std::vector<Vec2> path) {
	this->path = path;
}

void Enemy::MoveToward(Vec2 target, float dt) {
	Vec2 forward = target - position;

	float distance = sqrt(forward.x * forward.x + forward.y * forward.y);
	if (distance != 0) {
		forward /= distance;
		position += forward * speed * dt;
	}
	UpdateRotation(forward, dt);
}

void Enemy::UpdateRotation(Vec2 direction, float dt) {
	float targetRotation = atan2(direction.y, direction.x) * (180/PI);

	float difference = targetRotation - rotation;
	if (difference > 180) difference -= 360;
	else if (difference < -180) difference += 360;

	if (difference > 0) {
		rotation += rotationSpeed * dt; 	}
	else if (difference < 0) {
		rotation -= rotationSpeed * dt;
	}
}