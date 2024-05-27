#include "gameManager.h"

gameManager::gameManager(){
	castleLife = castleMaxLife;
}

gameManager::~gameManager(){
}

void gameManager::Update(float dt) {
	if (!gameOver)
		return;

	delay += 1 * dt;
	if (delay >= 5)
		restart = true;
}

void gameManager::Draw() {
	if (!gameOver)
		return;

	DrawText("GAME OVER", 250, 260, 100, BLACK);
}

void gameManager::ApplyDamage(int amount) {
	castleLife -= amount;
	if (castleLife <= 0) {
		CastleDead();
		castleLife = 0;
	}
	std::cout << castleLife << std::endl;
}

void gameManager::ApplyRegen(int amount) {
	castleLife += amount;
	if (castleLife > castleMaxLife)
		castleLife = castleMaxLife;
}

void gameManager::AddMoney(int amount) {
	money += amount;
}

void gameManager::SubtractMoney(int amount) {
	money -= amount;
}

void gameManager::CastleDead() {
	gameOver = true;
}

int gameManager::GetMoney() {
	return money;
}

bool gameManager::GetRestart() {
	return restart;
}

int gameManager::GetLife()
{
	return castleLife;
}
