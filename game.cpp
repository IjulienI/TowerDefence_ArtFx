#include "game.h"

Game::Game() {
	Init();
}

Game::Game(int index) {
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
	Load();
}

void Game::Update(float dt) {
	for (auto& enemy : enemies) {
		enemy->Update(dt);
;	}
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
}

void Game::Load()
{
	Texture2D road = LoadTexture("textures/road.png");
	Texture2D grass = LoadTexture("textures/grass.png");
	Texture2D finish = LoadTexture("textures/finish.png");
	Texture2D obstacle = LoadTexture("textures/obstacle.png");

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
			else if (pixels[j * mapImage.width + i].r == 0 && pixels[j * mapImage.width + i].g == 255 && pixels[j * mapImage.width + i].b == 21) {
				map[i][j]->SetTexture(grass);
				map[i][j]->SetType(TileType::GRASS);
			}
			else if (pixels[j * mapImage.width + i].r == 255 && pixels[j * mapImage.width + i].g == 0 && pixels[j * mapImage.width + i].b == 0) {
				map[i][j]->SetTexture(obstacle);
				map[i][j]->SetType(TileType::CASTLE);
				obstacles.push_back(map[i][j]);
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

	AlignPath(waypoints);

	Enemy* test = new Enemy();
	test->SetPath(waypoints);
	test->SetPosition(waypoints.front());
	enemies.push_back(test);
}

void Game::AlignPath(std::vector<Vec2>& waypoints) {
	int maxLoop = waypoints.size() * waypoints.size();
	std::vector<Vec2> cleanPath;
	cleanPath.push_back(waypoints[0]);
	auto it = std::remove(waypoints.begin(), waypoints.end(), waypoints[0]);
	waypoints.erase(it,waypoints.end());

	while (!waypoints.empty())
	{
		static int loopCount;
		for (int i = 0; i < waypoints.size(); i++) {
			Vec2 p1 = cleanPath.back();
			Vec2 p2 = waypoints[i];
			float distance = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
			if (distance == TILE_SIZE) {
				cleanPath.push_back(waypoints[i]);
				auto it = std::remove(waypoints.begin(), waypoints.end(), waypoints[i]);
				waypoints.erase(it, waypoints.end());
				loopCount = 0;
			}
			if (loopCount == 1) {
				if (distance == TILE_SIZE * 2) {
					cleanPath.push_back(waypoints[i]);
					auto it = std::remove(waypoints.begin(), waypoints.end(), waypoints[i]);
					waypoints.erase(it, waypoints.end());
					loopCount = 0;
				}
			}
		}
		loopCount++;
		if (loopCount >= 2) {
			break;
		}
		std::cout << loopCount << std::endl;
	}
	waypoints = cleanPath;
}