#include "towers.h"

Towers::Towers() {
}

Towers::Towers(std::vector<Enemy*> enemies) {
	SetEnemies(enemies);
}

Towers::~Towers() {
}

void Towers::Update(float dt) {
	for (auto& enemie : enemies) {
		Vec2 enemiePosition = enemie->GetPosition();
		float distance = position.Distance(enemiePosition);
		if (distance > targetDistance)
			return;

		float angle = position.AngleDegre(enemiePosition);
		rotation = angle;
	}
}

void Towers::Draw() {
}

void Towers::SetEnemies(std::vector<Enemy*> enemies) {
	this->enemies = enemies;
}
