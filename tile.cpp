#include "tile.h"

Tile::Tile() : position({0,0}) {
}

Tile::Tile(Vec2 position) {
	SetPosition(position);
}

Tile::~Tile() {
	UnloadTexture(texture);
	UnloadTexture(border);
	UnloadTexture(tileClicked);
}

void Tile::SetPosition(Vec2 position) {
	this->position = position;
}

void Tile::SetType(TileType type) {
	this->type = type;
}

void Tile::SetTexture(Texture2D& texture) {
	this->texture = texture;
}

void Tile::Draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
	if (isActivated) {
		if (isClicked) {
			DrawTexture(tileClicked, position.x, position.y, WHITE);			
		}
		else {
			DrawTexture(border, position.x, position.y, WHITE);
		}
		isActivated = false;
	}
}

Vec2 Tile::GetPosition() {
	return position;
}

Vec2 Tile::GetCenter() {
	return {position.x + TILE_SIZE / 2,position.y + TILE_SIZE / 2 };
}

TileType Tile::GetType() {
	return type;
}

bool Tile::GetActivated() {
	return isActivated;
}

void Tile::SetActivated(bool status) {
	isActivated = status;
}

void Tile::SetClicked(bool status) {
	isClicked = status;
}

bool Tile::Contains(Vec2 position) {
	return (position.x >= this->position.x && position.x <= this->position.x + TILE_SIZE && position.y >= this->position.y && position.y <= this->position.y + TILE_SIZE);
}
