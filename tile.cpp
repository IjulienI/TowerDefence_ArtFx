#include "tile.h"

Tile::Tile() : position({0,0}) {
}

Tile::Tile(Vec2 position) {
	SetPosition(position);
}

Tile::~Tile() {
	UnloadTexture(texture);
}

void Tile::SetPosition(Vec2 position) {
	this->position = position;
}

void Tile::SetType(TileType type) {
	this->type = type;
}

void Tile::SetTexture(Texture2D& texture) {
	if (IsTextureReady(texture)) {
		UnloadTexture(this->texture);
		this->texture = texture;
	}
}

void Tile::Draw() {
	DrawTexture(texture, position.x, position.y, WHITE);
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
