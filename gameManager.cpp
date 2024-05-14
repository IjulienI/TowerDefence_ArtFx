#include "gameManager.h"

gameManager::gameManager(){
	castleLife = castleMaxLife;
}

gameManager::~gameManager()
{
}

void gameManager::ApplyDamage(int amount) {
	castleLife -= amount;
	if (castleLife <= 0)
		CastleDead();
}

void gameManager::ApplyRegen(int amount) {
	castleLife += amount;
	if (castleLife > castleMaxLife)
		castleLife = castleMaxLife;
}

void gameManager::CastleDead() {
	std::cout << "Castle Destroyed" << std::endl;
}