#include "gameManager.h"

gameManager::gameManager(){
	castleLife = castleMaxLife;
}

gameManager::~gameManager(){
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
	std::cout << "Castle Destroyed" << std::endl;
}

int gameManager::GetMoney() {
	return money;
}
