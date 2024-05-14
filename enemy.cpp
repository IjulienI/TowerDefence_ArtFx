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
	//DrawTexturePro(texture,)
	DrawCircle(position.x, position.y, 15, BLACK);
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
	Vec2 direction = target - position;

	float distance = sqrt(direction.x * direction.x + direction.y * direction.y);
	if (distance != 0) {
		direction /= distance;
		position += direction * speed * dt;
	}
	UpdateRotation(direction);
}

void Enemy::UpdateRotation(Vec2 direction) {
	rotation = atan2(direction.y, direction.x);
}