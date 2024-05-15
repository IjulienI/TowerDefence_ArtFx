#include "application.h"

Application* app = nullptr;

Application::Application()
{
	Init();	
}
Application::~Application(){
}

void Application::Init()
{
	InitWindow(WINDOW_SIZE.x, WINDOW_SIZE.y, "TowerDefence - ArtFx");
	SetTargetFPS(FRAME_LIMIT);

	sceneManager = new SceneManager();
	debug = new Debug();

	while (!WindowShouldClose()) {
		Update();
		Draw();
	}
	CloseWindow();
}

void Application::Update()
{
	float deltaTime = GetFrameTime();
	sceneManager->Update(deltaTime);
	debug->Update(deltaTime);
}

void Application::Draw()
{
	BeginDrawing();

	ClearBackground(BACKGROUND_COLORATION);

	sceneManager->Draw();
	debug->Draw();

	EndDrawing();
}
