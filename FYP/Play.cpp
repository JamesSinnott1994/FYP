#include "stdafx.h"
#include "Play.h"

Play::Play(b2World* w, int SCREEN_WIDTH, int SCREEN_HEIGHT):world(w), playerDead(false), levelComplete(false), framecounter(0)
{
	// Load player
	m_player = new Player();
	m_player->Init(SDL_Rect{ 200, 500, 77, 107 }, world);

	// Load background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/space.png", SDL_Rect{ 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT }, SDL_Rect{ 0, 0, 600, 360 });

	// Load level
	Level::LoadLevel("Text/Level1.txt", world);
}

void Play::Init()
{

}

void Play::Update()
{
	//Update Camera position
	UpdateCameraPos();

	//Step the world
	float32 timeStep = 1.0f / 4.0f;// Increase right-hand value to slow down
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(timeStep, velocityIterations, positionIterations);
	
	//Update game entities.
	m_player->Update();
}

void Play::Draw() {
	Renderer::GetInstance()->ClearRenderer();

	/*Call Draw on objects here*/
	AddAssetsToRenderer();

	Renderer::GetInstance()->RenderScreen();
}

void Play::AddAssetsToRenderer()
{
	m_backGroundImage->Draw(4);
	m_player->Draw();
	PlatformManager::GetInstance()->Draw();
	PickupManager::GetInstance()->Draw();
}

void Play::UpdateCameraPos()
{
	Renderer::GetInstance()->UpdateCameraPosition(m_player->getBody()->GetPosition().x);
}