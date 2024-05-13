#pragma once
#include "constant.h"
#include "tileType.h"
#include <iostream>

class Tile {
public:
	Tile();
	Tile(Vector2 position, Texture2D& texture);
	Tile(Vector2 position);
	~Tile();

	void SetType(TileType type);
	void SetTexture(Texture2D& texture);
	void Draw();

	Vector2 GetPosition();
	Vector2 GetCenter();
	TileType GetType();

	bool GetActivated();
	void SetActivated(bool status);
private:
	Vector2 position;
	TileType type;
	Texture2D texture;

	bool isActivated;
};

