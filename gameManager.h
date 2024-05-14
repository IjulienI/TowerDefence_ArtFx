#pragma once

#include <iostream>

class gameManager
{
private:
	int castleLife = 0;
	int castleMaxLife = 100;

	int currentRound = 0;
	int maxRound = 5;

	int enemyCount = 0;
	int enemyPerWave = 2;

	int currentWaveCount = 0;
	int nextWaveCount = 15;
public:
	gameManager();
	~gameManager();

	void ApplyDamage(int amount);
	void ApplyRegen(int amount);
	void CastleDead();
};