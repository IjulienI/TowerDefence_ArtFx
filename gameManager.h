#pragma once

#include <iostream>
#include <raylib.h>

class gameManager
{
private:
	int castleLife = 0;
	int castleMaxLife = 5000;

	int currentRound = 0;
	int maxRound = 5;

	int enemyCount = 0;
	int enemyPerWave = 2;

	int currentWaveCount = 0;
	int nextWaveCount = 15;

	int money = 100;

	float delay = 0;
	bool gameOver = false;
	bool restart = false;
public:
	gameManager();
	~gameManager();

	void Update(float dt);
	void Draw();

	void ApplyDamage(int amount);
	void ApplyRegen(int amount);
	void AddMoney(int amount);
	void SubtractMoney(int amount);
	void CastleDead();
	int GetMoney();
	bool GetRestart();
	int GetLife();
};