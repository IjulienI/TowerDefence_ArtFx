#include "tile.h"

Tile::Tile() {
	this->position = {0,0};
	this->texture = LoadTexture("textures/base.png");
	this->type = GRASS;
	this->isActivated = false;
}

Tile::Tile(Vector2 position, Texture2D& texture) {
	this->position = position;
	this->texture = texture;
	this->type = GRASS;
	this->isActivated = false;
}

Tile::Tile(Vector2 position) {
	this->position = position;
	this->texture = LoadTexture("textures/base.png");
	this->type = GRASS;
	this->isActivated = false;
}

Tile::~Tile() {
	UnloadTexture(texture);
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

Vector2 Tile::GetPosition() {
	return position;
}

Vector2 Tile::GetCenter() {
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
