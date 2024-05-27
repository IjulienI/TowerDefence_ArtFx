#pragma once

#include "enemy.h"
#include <vector>
#include "Vec2.h"
#include "gameManager.h"
#include <cstdlib> 
#include <ctime>

class EnemySpawner
{
private:
	std::vector<Enemy*> enemies;
	std::vector<Vec2> waypoints;

	gameManager* gm = nullptr;

	int waveCount = 0;
	int enemiesCount = 0;
	int enemiesPerWave = 0;

	float delay = 0;
	float timeBtwEnemies = 1.5;

	bool inWave = true;
	bool startCounter = false;

	void SpawnRandomEnemy();
	void SpawnNewEnemy(Enemy* type);
	void StartBossWave();
public:
	EnemySpawner();
	~EnemySpawner();

	void Update(float dt);
	void Draw();

	std::vector<Enemy*> GetEnemies();

	void StartWave();
	void SetWayPoints(std::vector<Vec2> waypoint);
	void SetGameMode(gameManager* gm);
	int genererNombreAleatoire(int min, int max);
};

