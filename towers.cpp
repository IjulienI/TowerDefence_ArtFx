#include "towers.h"

Enemy* Towers::GetNearestEnemy(std::vector<Enemy*> enemies) {
	if (enemies.size() <= 0)
		return nullptr;

	Enemy* nearest = enemies[0];
	float lastDistance = 0;

	for (auto& enemy : enemies) {
		Vec2 enemyPos = enemy->GetPosition();
		float distance = position.Distance(enemyPos);

		if (distance < lastDistance) {
			nearest = enemy;
			lastDistance = distance;
		}
	}
	return nearest;
}

void Towers::SetRotation() {
	if (!nearestEnemy)
		return;

	Vec2 forward = nearestEnemy->GetPosition() - position;
	rotation = atan2(forward.y, forward.x) * (180 / PI);
}

Towers::Towers() {
}

Towers::Towers(std::vector<Enemy*> enemies) {
	SetEnemies(enemies);
}

Towers::~Towers() {
	UnloadTexture(turret);
}

void Towers::Update(float dt) {
	nearestEnemy = GetNearestEnemy(enemies);
	SetRotation();
}

void Towers::Draw() {
	Rectangle tower = { position.x,position.y,size.x,size.y };

	DrawTexturePro(turret, { 0,0,(float)turret.width,(float)turret.height }, tower, { size.x / 2,size.y / 2 }, rotation, WHITE);
}

void Towers::SetEnemies(std::vector<Enemy*> enemies) {
	this->enemies = enemies;
}

void Towers::SetPosition(Vec2 position) {
	this->position = position;
}
