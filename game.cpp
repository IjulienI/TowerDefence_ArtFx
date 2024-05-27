#include "game.h"

Game::Game() {
	LoadMap();
	Init();
}

Game::Game(int index) {
	this->mapIndex = index;
	LoadMap();
	Init();
}

Game::~Game() {
	for (int i = 0; i < TILE_NUM.x; i++) {
		for (int j = 0; j < TILE_NUM.y; j++) {
			delete map[i][j];
		}
	}
}

void Game::Init() {
	enemySpawner = new EnemySpawner();
	enemySpawner->SetGameMode(&gm);
	enemySpawner->SetWayPoints(waypoints);
	enemySpawner->StartWave();
}

void Game::Update(float dt) {
	MouseSystem();
	Inputs();

	enemySpawner->Update(dt);

	for (auto& tower : towers) {
		tower->SetEnemies(enemySpawner->GetEnemies());
		tower->Update(dt);
		if (tower->CanShoot(dt)) {
			Ball* ball = new Ball();
			ball->SetPositionAndRotation(tower->GetPosition(), tower->GetRotation());
			ball->SetDamage(tower->GetDamage());
			balls.push_back(ball);
		}
	}

	for (auto& ball : balls) {
		if (ball->GetDeath()) {

			auto it = std::remove(balls.begin(), balls.end(), ball);
			ball->~Ball();
			balls.erase(it, balls.end());
		}

		ball->Update(dt);
		for (auto& enemy : enemySpawner->GetEnemies()) {
			if (ball->DetectCollision(enemy)) {
				enemy->ApplyDamage(ball->GetDamage());

				auto it = std::remove(balls.begin(), balls.end(), ball);
				ball->~Ball();
				balls.erase(it, balls.end());

			}
		}
	}

	gm.Update(dt);

	if (gm.GetRestart())
		sceneManager->ChangeScene(Scenes::MENU);
}

void Game::Draw() {	
	for (int i = 0; i < TILE_NUM.x; i++) {	
		for (int j = 0; j < TILE_NUM.y; j++) {
			map[i][j]->Draw();
		}
	}	

	for (auto& ball : balls) {
		ball->Draw();
	}

	for (auto& tower : towers) {
		tower->Draw();
	}

	enemySpawner->Draw();

	if (!mouseOn)
		return;

	if (mouseOn->GetType() == TileType::GRASS) {

		int needMoney = 50;

		Color canBuy;

		if (needMoney <= gm.GetMoney())
			canBuy = GREEN;
		else
			canBuy = RED;

		DrawRectangle(mousePos.x, mousePos.y, 125, 54, { 0,0,0,125 });

		DrawText(TextFormat("Buy tower : %i", needMoney), mousePos.x + 10, mousePos.y + 20, 16, canBuy);
	}

	if (displayPrice) {

		Towers* tower = mouseOn->GetTower();
		int needMoney = tower->GetPrice();
		int sellMoney = tower->GetSell();
		Color canBuy;
		if (needMoney <= gm.GetMoney())
			canBuy = GREEN;
		else
			canBuy = RED;

		DrawRectangle(mousePos.x, mousePos.y, 125, 72, { 0,0,0,125 });

		if(tower->IsLevelMax())
			DrawText("Upgrade : MAX", mousePos.x + 10, mousePos.y + 20, 16, YELLOW);
		else
			DrawText(TextFormat("Upgrade : %i", needMoney), mousePos.x + 10, mousePos.y + 20, 16, canBuy);

		DrawText(TextFormat("Sell : %i", sellMoney), mousePos.x + 10, mousePos.y + 40, 16, RED);
	}

	gm.Draw();
}

void Game::LoadMap()
{
	Image mapImage = LoadImage("textures/base.png");

	std::string path = "textures/maps";

	int index = 0;
	for (const auto& entry : std::filesystem::directory_iterator(path)) {
		if (entry.path().extension() == ".png") {
			std::string filePath = entry.path().string();
			if (index == mapIndex) {
				UnloadImage(mapImage);
				mapImage = LoadImage(filePath.c_str());
			}
			index++;
		}
	}
	Color* pixels = LoadImageColors(mapImage);

	int pixelIndex = 0;
	for (int i = 0; i < TILE_NUM.x; i++) {
		for (int j = 0; j < TILE_NUM.y; j++) {
			map[i][j] = new Tile({ (i * TILE_SIZE) + TILE_SPACER.x, (j * TILE_SIZE) + TILE_SPACER.y });
			if (pixels[j * mapImage.width + i].r == 0 && pixels[j * mapImage.width + i].g == 0 && pixels[j * mapImage.width + i].b == 0) {
				map[i][j]->SetTexture(road);
				map[i][j]->SetType(TileType::ROAD);
				waypoints.push_back(map[i][j]->GetCenter());
			}
			else if (pixels[j * mapImage.width + i].r == 255 && pixels[j * mapImage.width + i].g == 0 && pixels[j * mapImage.width + i].b == 255) {
				map[i][j]->SetTexture(road);
				map[i][j]->SetType(TileType::ROAD);
				start = map[i][j]->GetCenter();
			}
			else if (pixels[j * mapImage.width + i].r == 0 && pixels[j * mapImage.width + i].g == 255 && pixels[j * mapImage.width + i].b == 0) {
				map[i][j]->SetTexture(grass);
				map[i][j]->SetType(TileType::GRASS);
			}
			else if (pixels[j * mapImage.width + i].r == 255 && pixels[j * mapImage.width + i].g == 255 && pixels[j * mapImage.width + i].b == 255) {
				map[i][j]->SetTexture(finish);
				map[i][j]->SetType(TileType::TOWER);
			}
			pixelIndex++;
		}
	}
	UnloadImage(mapImage);
	UnloadImageColors(pixels);

	CleanPath(waypoints);
}

void Game::CleanPath(std::vector<Vec2>& waypoints) {
	std::vector<Vec2> cleanPath;
	cleanPath.push_back(start);

	int loopCount = 0;
	float lastAngle = 0;

	while (!waypoints.empty())
	{
		for (int i = 0; i < waypoints.size(); i++) {
			Vec2 p1 = cleanPath.back();
			Vec2 p2 = waypoints[i];

			float distance = p1.Distance(p2);
			float angle = p1.Angle(p2);

			//si la prochaine case est en face et a la bonne distance
			if (distance == TILE_SIZE && angle == lastAngle) {
				cleanPath.push_back(waypoints[i]);
				auto it = std::remove(waypoints.begin(), waypoints.end(), waypoints[i]);
				waypoints.erase(it, waypoints.end());
				loopCount = 0;
			}
			//sinon est ce qu'elle est juste a la bonne distance
			else if (loopCount == 2 && distance == TILE_SIZE) {
				lastAngle = angle;
				cleanPath.push_back(waypoints[i]);
				auto it = std::remove(waypoints.begin(), waypoints.end(), waypoints[i]);
				waypoints.erase(it, waypoints.end());
				loopCount = 0;
			}
			//sinon est ce qu'elles est a une case et dans la bonne direction
			else if (loopCount == 3 && distance == TILE_SIZE * 2 && angle == lastAngle) {
				cleanPath.push_back(waypoints[i]);
				auto it = std::remove(waypoints.begin(), waypoints.end(), waypoints[i]);
				waypoints.erase(it, waypoints.end());
				loopCount = 0;
			}
		}
		loopCount++;
		if (loopCount >= 10) {
			break;
		}
	}
	waypoints = cleanPath;
}

Tile* Game::GetTileAtLocation(Vec2 location) {	
	for (int i = 0; i < TILE_NUM.x; i++) {
		for (int j = 0; j < TILE_NUM.y; j++) {
			if (map[i][j]->Contains(location))
				return map[i][j];
		}
	}
	return nullptr;
}

void Game::MouseSystem() {
	mousePos = { GetMousePosition().x,GetMousePosition().y };

	mouseOn = GetTileAtLocation(mousePos);
	if (!mouseOn)
		return;
	mouseOn->SetActivated(true);

	if (mouseOn->GetType() == TileType::TOWER)
		displayPrice = true;
	else
		displayPrice = false;
}

void Game::Inputs() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		if (!mouseOn)
			return;

		mouseOn->SetClicked(true);
		if (mouseOn->GetType() == TileType::GRASS) {
			if (gm.GetMoney() >= 50) {
				gm.SubtractMoney(50);
				mouseOn->SetType(TileType::TOWER);
				mouseOn->SetTexture(turretBase);
				Towers* tower = new Towers();
				tower->Interact();
				tower->SetPosition(mouseOn->GetCenter());
				tower->SetEnemies(enemySpawner->GetEnemies());
				mouseOn->SetTower(tower);
				towers.push_back(tower);
			}
		}
		if (mouseOn->GetType() == TileType::TOWER) {
			Towers* tower = mouseOn->GetTower();
			if (!(tower->GetCanInteract() && tower->CanUpgrade() && gm.GetMoney() >= tower->GetPrice()))
				return;

			tower->Interact();
			gm.SubtractMoney(tower->GetPrice());
			tower->Upgrade();
		}
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		if (!mouseOn)
			return;

		mouseOn->SetClicked(false);
	}
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		if (!mouseOn || mouseOn->GetType() != TileType::TOWER)
			return;

		Towers* tower = mouseOn->GetTower();
		gm.AddMoney(tower->GetSell());
		auto it = std::remove(towers.begin(), towers.end(), tower);
		tower->~Towers();
		towers.erase(it, towers.end());
		mouseOn->SetType(TileType::GRASS);
		mouseOn->SetTexture(grass);
	}
}
