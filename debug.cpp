#include "debug.h"

Debug* debug = nullptr;

Debug::Debug()
{
	deltaTime = 0;
}

Debug::~Debug()
{
}

void Debug::Draw()
{
	DrawText(TextFormat("FPS: %i", (int)(1.0f / deltaTime)), 5, 5, 5, GREEN);
}

void Debug::Update(float dt)
{
	deltaTime = dt;
}