#include "enemySpawner.h"

std::vector<Enemy*> EnemySpawner::GetEnemies() {
    return enemies;
}

void EnemySpawner::StartWave() {
	enemiesPerWave = genererNombreAleatoire(10, 25);
	enemiesCount = 0;
	inWave = true;
}

void EnemySpawner::SetWayPoints(std::vector<Vec2> waypoint){
	this->waypoints = waypoint;
}

void EnemySpawner::SetGameMode(gameManager* gm) {
	this->gm = gm;
}

int EnemySpawner::genererNombreAleatoire(int min, int max) {
	return min + rand() % (max - min + 1);
}

void EnemySpawner::SpawnRandomEnemy() {
	int rng = genererNombreAleatoire(0, 100);
	if (rng < 50) {
		Enemy* test = new SmallEnemy(gm);
		SpawnNewEnemy(test);
	}
	else if (rng < 75) {
		Enemy* test = new MidEnemy(gm);
		SpawnNewEnemy(test);
	}
	else {
		Enemy* test = new BigEnemy(gm);
		SpawnNewEnemy(test);
	}
}

void EnemySpawner::SpawnNewEnemy(Enemy* test) {
	test->SetPath(waypoints);
	test->SetPosition(waypoints.front());
	test->SetLifeMultiplier(waveCount);
	enemies.push_back(test);
}

void EnemySpawner::StartBossWave() {
	Enemy* test = new Boss(gm);
	SpawnNewEnemy(test);
	enemiesCount = 0;
	enemiesPerWave = 1;
	inWave = true;
}

EnemySpawner::EnemySpawner() {
}

EnemySpawner::~EnemySpawner() {
}

void EnemySpawner::Update(float dt) {
	delay += 1 * dt;
	if (inWave) {
		if (delay >= timeBtwEnemies) {
			delay = 0;
			SpawnRandomEnemy();
			timeBtwEnemies = genererNombreAleatoire(1,3);
			enemiesCount++;
		}
		if (enemiesCount == enemiesPerWave) {
			inWave = false;
			delay = 0;
		}
	}
	else if (enemies.size() == 0 && !startCounter) {
		startCounter = true;
		delay = 0;
	}
	else if (startCounter && delay >= 5) {
		startCounter = false;
		waveCount++;

		if (waveCount % 5 == 0)
			StartBossWave();
		else
			StartWave();
	}

	for (auto& enemy : enemies) {
		if (enemy->GetDeath()) {			
			gm->AddMoney(enemy->GetDrop());
			auto it = std::remove(enemies.begin(), enemies.end(), enemy);
			enemies.erase(it, enemies.end());
		}
	}
	for (auto& enemy : enemies) {
		enemy->Update(dt);
	}
}

void EnemySpawner::Draw() {
	for (auto& enemy : enemies) {
		enemy->Draw();
	}

	//C'est ignoble sais mais je l'ai fait a la derniere minute >;(
	DrawRectangle(50, 25, 125, 72, { 0,0,0,125 });
	DrawText(TextFormat("ENEMY : %i / %i", enemiesCount, enemiesPerWave), 50, 25, 16, BLACK);
	DrawText(TextFormat("WAVE  : %i", waveCount), 50, 40, 16, BLACK);
	DrawText(TextFormat("MONEY : %i", gm->GetMoney()), 50, 55, 16, BLACK);
	DrawText(TextFormat("LIFE  : %i", gm->GetLife()), 50, 70, 16, BLACK);
}
