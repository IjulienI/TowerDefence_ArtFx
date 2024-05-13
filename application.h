#pragma once
#include "constant.h"
#include "debug.h"
#include "sceneManager.h"

class Application
{
public:
	Application();
	~Application();
private:
	void Init();
	void Update();
	void Draw();
};

extern Application* app;