#include "stdafx.h"
#include "Play.h"

Play::Play(b2World* w, int SCREEN_WIDTH, int SCREEN_HEIGHT, Splash* pSplash)
{
	Init(w, SCREEN_WIDTH, SCREEN_HEIGHT, pSplash);
}

void Play::Init(b2World* w, int SCREEN_WIDTH, int SCREEN_HEIGHT, Splash* pSplash)
{
	levelComplete = false;
	world = w;

	// Splash screen object
	splash = pSplash;

	// Timer
	timer = new Timer();

	// Which speed to use
	//whichSpeed = "labSpeed";
	whichSpeed = "laptopSpeed";

	// Load player
	m_player = new Player();
	float playerScale = 0.9f;
	m_player->Init(SDL_Rect{ 200, 500, 77 * playerScale, 107 * playerScale }, world, whichSpeed, playerScale);
	m_healthBar = new HealthBar();

	// Screen width and height
	m_width = SCREEN_WIDTH;
	m_height = SCREEN_HEIGHT;

	// Load background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/space.png", SDL_Rect{ 0, 0, m_width * 2, m_height }, SDL_Rect{ 0, 0, 600, 360 });

	// Load level
	level = new Level();
	level->LoadLevel("Text/Level1.txt", world, whichSpeed, m_width, m_height);

	// For text
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

	levelComplete = false;

	fontLoaded = false;

	// Menu
	menuOpen = false;
	paused = false;
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
	if (!fontLoaded)
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
	fontLoaded = true;
	return success;
}

int Play::Update(SDL_Event e)
{
	// Play music
	SoundManager::GetInstance()->play(SoundManager::GetInstance()->LEVEL_TWO_MUSIC);

	// Update Camera position
	UpdateCameraPos();

	//Step the world
	float32 timeStep = 1.0f / speedToUse;// Increase right-hand value to slow down
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	world->Step(timeStep, velocityIterations, positionIterations);

	// Call Reset() if player not alive
	if (!m_player->GetAlive())
	{
		Reset();
	}

	// Call LevelComplete() if player has reached teleporter
	if (m_player->GetReachedTeleporter() && !levelComplete)
	{
		LevelComplete();
	}
	else // Update game
	{
		// Not paused
		if (!paused)
		{
			m_player->Update();

			// Increment player score if collided with coin
			if (m_player->CheckScoreCollision())
			{
				m_player->SetScore(m_player->GetScore() + 10);
				loadTTFMedia();
			}

			ObstacleManager::GetInstance()->Update();
			Teleporter::GetInstance()->Update();
			PickupManager::GetInstance()->Update();
			// Checks if player collides with enemy bullets
			if (EnemyManager::GetInstance()->Update(m_player->GetPosition(), m_player->getBody()))
			{
				//m_player->SetHealth(m_player->GetHealth() - 10);
			}
			// Opens menu
			if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_o) && !menuOpen)
			{
				menuOpen = true;
				paused = true;
			}
		}// End if

		// Paused
		if (paused)
		{
			if (InGameMenu::GetInstance()->Update(e) == 0)
			{
				paused = false;
				menuOpen = false;
			}
			if (InGameMenu::GetInstance()->Update(e) == 2)
			{
				return 2;
			}
		}// End if
	}// End else

	return 0;
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
		EnemyManager::GetInstance()->Reset();
		EnemyManager::GetInstance()->DestroyBullets();
		paused = false;
		menuOpen = false;
	}
}

void Play::Quit()
{
	m_player->Reset();
	PickupManager::GetInstance()->Reset();
	ObstacleManager::GetInstance()->Reset();
	EnemyManager::GetInstance()->Reset();
	PickupManager::GetInstance()->Destroy();
	ObstacleManager::GetInstance()->Destroy();
	PlatformManager::GetInstance()->Destroy();
	WallManager::GetInstance()->Destroy();
	EnemyManager::GetInstance()->Destroy();
	paused = false;
	menuOpen = false;
	splash->SetCanDraw(true);
}

void Play::LevelComplete()
{
	// Draw splash screen
	splash->SetCanDraw(true);

	// Increment level
	level->SetLevelNum(level->GetLevelNum() + 1);

	// Destroy objects
	PickupManager::GetInstance()->Destroy();
	ObstacleManager::GetInstance()->Destroy();
	PlatformManager::GetInstance()->Destroy();
	WallManager::GetInstance()->Destroy();
	EnemyManager::GetInstance()->Destroy();
	m_player->LevelComplete();

	// Get the next level text file
	string levelText = "Text/Level" + to_string(level->GetLevelNum()) + ".txt";
	level->LoadLevel(levelText, world, whichSpeed, m_width, m_height);

	m_backGroundImage->Init("Images/space2.png", SDL_Rect{ 0, 0, m_width * 2, m_height }, SDL_Rect{ 0, 0, 2560, 1024 });

	m_player->SetReachedTeleporter(false);
	levelComplete = true;

	loadTTFMedia();
}

void Play::Draw() 
{
	// For splash screen
	HandleSplash();

	Renderer::GetInstance()->ClearRenderer();
	if (!splash->CanDraw())// If we can't draw splash screen, then draw all other game assets
		AddAssetsToRenderer();
	else // Draw splash screen
		splash->Draw();
	Renderer::GetInstance()->RenderScreen();
}

void Play::AddAssetsToRenderer()
{
	m_backGroundImage->Draw(4);
	m_player->Draw();
	Teleporter::GetInstance()->Draw();
	PlatformManager::GetInstance()->Draw();
	PickupManager::GetInstance()->Draw();
	ObstacleManager::GetInstance()->Draw();
	EnemyManager::GetInstance()->Draw();

	// Draw Health Bar
	SDL_Color red = SDL_Color{ 255, 0, 0, 255 };
	SDL_Color green = SDL_Color{ 0, 255, 0, 255 };
	m_healthBar->RenderHPBar(550, 15, 200, 25, m_player->GetHealth()*0.01f, green, red);

	if (paused) // Draw In-Game menu
	{
		InGameMenu::GetInstance()->Draw(m_width, m_height);
	}

	// Draw text at position
	gScoreTextTexture.render(20, 10);
	gLevelTextTexture.render(300, 10);
}

void Play::HandleSplash()
{
	// Start timer if not already started
	if (splash->CanDraw())
	{
		if (!timer->isStarted())
		{
			timer->start();
		}

		// Reset after 2 seconds
		if (timer->getTicks() / 1000 >= 0.5f)
		{
			splash->SetCanDraw(false);
			timer->reset();
		}
	}
}

void Play::UpdateCameraPos()
{
	// Pass players position to Renderer::UpdateCameraPosition()
	Renderer::GetInstance()->UpdateCameraPosition(m_player->getBody()->GetPosition().x);
}