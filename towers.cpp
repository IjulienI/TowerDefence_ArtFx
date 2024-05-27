#include "towers.h"

Enemy* Towers::GetNearestEnemy(std::vector<Enemy*> enemies) {
	if (enemies.size() == 0)
		return nullptr;

	Enemy* nearest = nullptr;
	float lastDistance = range;

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

void Towers::ApplyNewLevel() {
	if(level == 1) {
		color = WHITE;
		shootDelay = 0.4;
		damage = 1;
		range = 150;
		moneyToUpgrade = 300;
		moneyToSell = moneyToUpgrade / 2;
	}
	if (level == 2) {
		color = GRAY;
		shootDelay = 0.2;
		damage = 1;
		range = 150;
		moneyToUpgrade = 1000;
		moneyToSell = 150;
	}
	else if (level == 3) {
		color = YELLOW;
		shootDelay = 0.3;
		damage = 2;
		range = 165;
		moneyToUpgrade = 1500;
		moneyToSell = 500;
	}
	else if (level == 4) {
		color = RED;
		shootDelay = 0.2;
		damage = 3;
		range = 165;
		moneyToUpgrade = 5000;
		moneyToSell = 750;
	}
	else if (level == 5) {
		color = BLUE;
		shootDelay = 0.1;
		damage = 10;
		range = 220;
		moneyToUpgrade = 0;
		moneyToSell = 2500;
		size = { 30,25 };
	}
}

bool Towers::CanShoot(float dt) {
	if (!nearestEnemy)
		return false;

	shootDelayCount += 1 * dt;
	if (shootDelayCount >= shootDelay) {
		shootDelayCount = 0;
		return true;
	}

	return false;
}

Towers::Towers() {
	shootDelayCount = shootDelay;
}

Towers::Towers(std::vector<Enemy*> enemies) {
	shootDelayCount = shootDelay;
	SetEnemies(enemies);
}

Towers::~Towers() {
}

void Towers::Update(float dt) {
	nearestEnemy = GetNearestEnemy(enemies);
	SetRotation();
	if (canInteract)
		return;

	interactionDelayCount += 1 * dt;
	if (interactionDelayCount >= interactionDelay) {
		interactionDelayCount = 0;
		canInteract = true;
	}
}

void Towers::Draw() {
	Rectangle tower = { position.x,position.y,size.x,size.y };

	DrawTexturePro(turret, { 0,0,(float)turret.width,(float)turret.height }, tower, { size.x / 2,size.y / 2 }, rotation, color);

	if (hightLight) {
		DrawCircleLines(position.x, position.y, range, { 0,0,0,60 });
		hightLight = false;
	}

	if(nearestEnemy)
		DrawLine(position.x, position.y, nearestEnemy->GetPosition().x, nearestEnemy->GetPosition().y, GREEN);

	DrawText(TextFormat("%i", level), position.x + TILE_SIZE /2, position.y + TILE_SIZE / 2, 16, BLACK);
}

void Towers::SetEnemies(std::vector<Enemy*> enemies) {
	this->enemies = enemies;
}

Vec2 Towers::GetPosition() {
	return position;
}

float Towers::GetRotation() {
	return rotation;
}

bool Towers::GetCanInteract() {
	return canInteract;
}

void Towers::SetHighLight(bool value) {
	hightLight = value;
}

int Towers::GetDamage() {
	return damage;
}

bool Towers::CanUpgrade() {
	return level < maxLevel;
}

int Towers::GetPrice() {
	return moneyToUpgrade;
}

int Towers::GetSell() {
	return moneyToSell;
}

bool Towers::IsLevelMax() {
	return level == maxLevel;
}

void Towers::Interact() {
	canInteract = false;
}

void Towers::Upgrade() {
	level++;
	ApplyNewLevel();
}

void Towers::SetPosition(Vec2 position) {
	this->position = position;
}
