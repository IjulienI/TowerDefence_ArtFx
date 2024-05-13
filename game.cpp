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
	LoadTiles();
}

void Game::Update(float dt) {
}

void Game::Draw() {	
	for (int i = 0; i < TILE_NUM.x; i++) {	
		for (int j = 0; j < TILE_NUM.y; j++) {
			map[i][j]->Draw();
		}
	}
}

void Game::LoadTiles()
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
				map[i][j]->SetType(ROAD);
			}
			else if (pixels[j * mapImage.width + i].r == 0 && pixels[j * mapImage.width + i].g == 255 && pixels[j * mapImage.width + i].b == 21) {
				map[i][j]->SetTexture(grass);
				map[i][j]->SetType(GRASS);
			}
			else if (pixels[j * mapImage.width + i].r == 255 && pixels[j * mapImage.width + i].g == 0 && pixels[j * mapImage.width + i].b == 0) {
				map[i][j]->SetTexture(obstacle);
				map[i][j]->SetType(OBSTACLE);
				obstacles.push_back(map[i][j]);
			}
			else if (pixels[j * mapImage.width + i].r == 255 && pixels[j * mapImage.width + i].g == 255 && pixels[j * mapImage.width + i].b == 255) {
				map[i][j]->SetTexture(finish);
				map[i][j]->SetType(FINISH);
			}
			else if (pixels[j * mapImage.width + i].r == 0 && pixels[j * mapImage.width + i].g == 0 && pixels[j * mapImage.width + i].b == 255) {
				map[i][j]->SetTexture(road);
				map[i][j]->SetType(CHECKPOINTS);
				checkPoints.push_back(map[i][j]);
			}
			pixelIndex++;
		}
	}
	UnloadImage(mapImage);
	UnloadImageColors(pixels);
}
