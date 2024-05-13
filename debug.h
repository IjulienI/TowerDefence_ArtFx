#pragma once
#include <raylib.h>

class Debug
{
public:
	Debug();
	~Debug();
	void Update(float dt);
	void Draw();
private:
	float deltaTime;
};
extern Debug* debug;
