#include "ball.h"


void Ball::WallCollision()
{
	if (position.x < radius) {
		needToBeDestroy = true;
	}
	else if (position.x + radius > WINDOW_SIZE.x) {
		needToBeDestroy = true;
	}
	if (position.y < radius) {
		needToBeDestroy = true;
	}
	else if (position.y + radius > WINDOW_SIZE.y) {
		needToBeDestroy = true;
	}
}

void Ball::Movement(float dt)
{
	Vec2 forward = { cos(rotation * (PI / 180)), sin(rotation * (PI / 180)) };

	position += forward * speed * dt;
}

bool Ball::DetectCollision(Enemy* enemy)
{
	int xMinA = (int)position.x - radius;
	int yMinA = (int)position.y - radius;
	int xMaxA = (int)position.x + radius;
	int yMaxA = (int)position.y + radius;
	int xMinB = (int)enemy->GetPosition().x - enemy->GetRadius();
	int yMinB = (int)enemy->GetPosition().y - enemy->GetRadius();
	int xMaxB = (int)enemy->GetPosition().x + enemy->GetRadius();
	int yMaxB = (int)enemy->GetPosition().y + enemy->GetRadius();

	if (!(xMinB > xMaxA || yMinB > yMaxA || xMaxB < xMinA || yMaxB < yMinA)) {
		if (position.x - radius < enemy->GetPosition().x) {
			enemy->ApplyDamage(10);
			return true;
		}
		if (position.x + radius > enemy->GetPosition().x + enemy->GetSize().x) {
			enemy->ApplyDamage(10);
			return true;
		}
		if (position.y - radius < enemy->GetPosition().y) {
			enemy->ApplyDamage(10);
			return true;
		}
		if (position.y + radius > enemy->GetPosition().y + enemy->GetSize().y) {
			enemy->ApplyDamage(10);
			return true;
		}
	}
	return false;
}

bool Ball::GetDeath() {
	return needToBeDestroy;
}

Ball::Ball()
{
}

Ball::~Ball()
{
}

void Ball::Update(float dt)
{
	Movement(dt);
	WallCollision();
}

void Ball::Draw()
{
	DrawCircle(position.x, position.y, radius, color);
}

void Ball::SetDamage(const int damage) {
	this->damage = damage;
}

int Ball::GetDamage() {
	return damage;
}

void Ball::SetPositionAndRotation(const Vec2 position, const float rotation) {
	this->position = position;
	this->rotation = rotation;
}
