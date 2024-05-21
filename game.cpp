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

	Enemy* test = new Boss(&gm);
	test->SetPath(waypoints);
	test->SetPosition(waypoints.front());
	enemies.push_back(test);
}

void Game::Update(float dt) {
	MouseSystem();
	Inputs();

	for (int i = 0; i < enemies.size(); i++) {
		if (!enemies[i]->GetDeath()) {
			enemies[i]->Update(dt);
			break;
		}
		auto it = std::remove(enemies.begin(), enemies.end(), enemies[i]);
		enemies[i]->~Enemy();
		enemies.erase(it, enemies.end());

		for (auto& tower : towers)
			tower->SetEnemies(enemies);
;	}

	for (auto& tower : towers) {
		tower->Update(dt);
	}
}

void Game::Draw() {	
	for (int i = 0; i < TILE_NUM.x; i++) {	
		for (int j = 0; j < TILE_NUM.y; j++) {
			map[i][j]->Draw();
		}
	}

	for (auto& enemy : enemies) {
		enemy->Draw();
	}

	for (auto& tower : towers) {
		tower->Draw();
	}
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
	Vec2 mousePos = { GetMousePosition().x,GetMousePosition().y };

	mouseOn = GetTileAtLocation(mousePos);
	if (!mouseOn)
		return;
	mouseOn->SetActivated(true);
}

void Game::Inputs() {
	if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
		if (!mouseOn)
			return;

		mouseOn->SetClicked(true);
		if (mouseOn->GetType() == TileType::GRASS) {
			mouseOn->SetType(TileType::TOWER);
			mouseOn->SetTexture(turretBase);
			Towers* tower = new Towers();
			tower->SetPosition(mouseOn->GetCenter());
			tower->SetEnemies(enemies);
			towers.push_back(tower);
		}
	}
	if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
		if (!mouseOn)
			return;

		mouseOn->SetClicked(false);
	}
	if (IsKeyPressed(KEY_A)) {
		enemies[0]->SetDeath(true);
	}
	if (IsKeyPressed(KEY_D)) {
		enemies[0]->SetDeath(true);
	}
}
