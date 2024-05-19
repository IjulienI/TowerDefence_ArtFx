#pragma once

#include "constant.h"
#include "tileType.h"
#include "Vec2.h"
#include <iostream>

class Tile {
public:
	Tile();
	Tile(Vec2 position);
	~Tile();


	void Draw();	
	
	void SetPosition(Vec2 position);
	void SetType(TileType type);
	void SetTexture(Texture2D& texture);

	Vec2 GetPosition();
	Vec2 GetCenter();
	TileType GetType();

	bool GetActivated();
	void SetActivated(bool status);

	void SetClicked(bool status);

	bool Contains(Vec2 position);
private:
	Vec2 position = {0,0};
	TileType type = TileType::GRASS;
	Texture2D texture = LoadTexture("textures/base.png");
	Texture2D border = LoadTexture("textures/border.png");
	Texture2D tileClicked = LoadTexture("textures/clickedTile.png");

	bool isActivated = false;
	bool isClicked = false;
};

