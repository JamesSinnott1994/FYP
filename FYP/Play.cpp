#include "stdafx.h"
#include "Play.h"

Play::Play(b2World* w, int SCREEN_WIDTH, int SCREEN_HEIGHT):world(w), playerDead(false), levelComplete(false), framecounter(0)
{
	// Timer
	timer = new Timer();

	// Which speed to use
	string whichSpeed = "labtopSpeed";

	// Load player
	m_player = new Player();
	m_player->Init(SDL_Rect{ 200, 500, 77, 107 }, world, whichSpeed);

	m_healthBar = new HealthBar();

	// Load background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/space.png", SDL_Rect{ 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT }, SDL_Rect{ 0, 0, 600, 360 });

	// Load level
	level = new Level();
	level->LoadLevel("Text/Level1.txt", world, whichSpeed);

	initializeTTF();
	loadTTFMedia();

	// Different speeds
	labComputerSpeed = 30.0f;
	laptopSpeed = 4.0f;

	if (whichSpeed == "labSpeed")
	{
		speedToUse = labComputerSpeed;
	}
	else
	{
		speedToUse = laptopSpeed;
	}
}

bool Play::initializeTTF()
{
	//Loading success flag
	bool success = true;

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		success = false;
	}

	//Initialize SDL_ttf
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	return success;
}

bool Play::loadTTFMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("Font/ARDESTINE.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 165, 0 };
		if (!gScoreTextTexture.loadFromRenderedText("Score: " + to_string(m_player->GetScore()), textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!gLevelTextTexture.loadFromRenderedText("Level: " + to_string(level->GetLevelNum()), textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void Play::Init()
{

}

void Play::Update()
{
	//Update Camera position
	UpdateCameraPos();

	//Step the world
	float32 timeStep = 1.0f / speedToUse;// Increase right-hand value to slow down
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(timeStep, velocityIterations, positionIterations);
	
	//Update game entities.
	m_player->Update();

	if (m_player->CheckScoreCollision())
	{
		m_player->SetScore(m_player->GetScore() + 10);
		loadTTFMedia();
	}

	ObstacleManager::GetInstance()->Update();
	//Teleporter::GetInstance()->Update();

	// Call Reset() if player not alive
	if (!m_player->GetAlive())
	{
		Reset();
	}
}

void Play::Reset()
{
	// Start timer if not already started
	if (!timer->isStarted())
	{
		timer->start();
	}
	// Reset after 2 seconds
	if (timer->getTicks() / 1000 >= 2)
	{
		timer->reset();
		m_player->Reset();
		loadTTFMedia();
		PickupManager::GetInstance()->Reset();
		ObstacleManager::GetInstance()->Reset();
	}
}

void Play::Draw() 
{
	Renderer::GetInstance()->ClearRenderer();

	/*Call Draw on objects here*/
	AddAssetsToRenderer();

	Renderer::GetInstance()->RenderScreen();
}

void Play::AddAssetsToRenderer()
{
	m_backGroundImage->Draw(4);
	m_player->Draw();
	//Teleporter::GetInstance()->Draw();
	PlatformManager::GetInstance()->Draw();
	PickupManager::GetInstance()->Draw();
	ObstacleManager::GetInstance()->Draw();

	SDL_Color red = SDL_Color{ 255, 0, 0, 255 };
	SDL_Color green = SDL_Color{ 0, 255, 0, 255 };

	m_healthBar->RenderHPBar(550, 15, 200, 25, m_player->GetHealth()*0.01f, green, red);

	// Draw text at position
	gScoreTextTexture.render(20, 10);
	gLevelTextTexture.render(300, 10);
}

void Play::UpdateCameraPos()
{
	Renderer::GetInstance()->UpdateCameraPosition(m_player->getBody()->GetPosition().x);
}