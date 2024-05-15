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
			else if (pixels[j * mapImage.width + i].r == 255 && pixels[j * mapImage.width + i].g == 0 && pixels[j * mapImage.width + i].b == 255) {
				map[i][j]->SetTexture(road);
				map[i][j]->SetType(TileType::ROAD);
				start = map[i][j]->GetCenter();
			}
			else if (pixels[j * mapImage.width + i].r == 0 && pixels[j * mapImage.width + i].g == 255 && pixels[j * mapImage.width + i].b == 0) {
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

	CleanPath(waypoints);

	Enemy* test = new Enemy();
	test->SetPath(waypoints);
	test->SetPosition(waypoints.front());
	enemies.push_back(test);
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
			float distance = sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
			float angle = Angle(p1, p2);

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

float Game::Angle(const Vec2& a, const Vec2& b) {
	float opposite = abs(a.x - b.x);
	float adjacent = abs(a.y - b.y);

	float angle = atan2(opposite, adjacent);

	return angle;
}
