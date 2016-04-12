#include "stdafx.h"
#include "Tutorial.h"

Tutorial::Tutorial()
{

}

Tutorial::Tutorial(int windowWidth, int windowHeight)
{
	// Create background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/Backgrounds/space4.png",
		SDL_Rect{ windowWidth / 2, windowHeight / 2, windowWidth, windowHeight }, SDL_Rect{ 0, 0, 3840, 2400 });
	m_backGroundImage->SetOffset(SDL_Point{ windowWidth / 2, windowHeight / 2 });

	// Right arrow
	m_rightArrow = new Sprite();
	m_rightArrow->Init("Images/Tutorial/RightArrow.png",
		SDL_Rect{ windowWidth - 60, (windowHeight / 2) - 34, 52, 69 }, SDL_Rect{ 0, 0, 52, 69 });

	// Left arrow
	m_leftArrow = new Sprite();
	m_leftArrow->Init("Images/Tutorial/LeftArrow.png",
		SDL_Rect{ 10, (windowHeight / 2) - 34, 52, 69 }, SDL_Rect{ 0, 0, 52, 69 });

	// Screen Number
	screenNo = 1;

	// Screen Image
	m_screenImage = new Sprite();
	m_screenImage->Init("Images/Tutorial/Screen" + to_string(screenNo) + ".png",
		SDL_Rect{ windowWidth *0.1f, windowHeight * 0.1f, windowWidth * 0.8f, windowHeight * 0.8f }, SDL_Rect{ 0, 0, 800, 600 });

	// Timer
	timer = new Timer();

	// Bool
	m_drawLeftArrow = false;
	m_drawRightArrow = true;

	initializeTTF();
	loadTTFMedia();
}

bool Tutorial::initializeTTF()
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

bool Tutorial::loadTTFMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("Font/timesbd.ttf", 20);
	gFont2 = TTF_OpenFont("Font/FORTE.ttf", 20);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 165, 0 };
		if (!returnText.loadFromRenderedText("Press 'Enter' to return", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void Tutorial::Draw()
{
	Renderer::GetInstance()->ClearRenderer();

	m_backGroundImage->DrawNoCamOffset();

	if (m_drawRightArrow)
		m_rightArrow->DrawNoCamOffset();
	if (m_drawLeftArrow)
		m_leftArrow->DrawNoCamOffset();

	SDL_Rect outerRect = { 80 - 5, 60 - 5, 640 + 10, 480 + 10 };
	SDL_SetRenderDrawColor(Renderer::GetInstance()->Get_SDL_RENDERER(), 0, 162, 232, 255);// LightBlue
	SDL_RenderFillRect(Renderer::GetInstance()->Get_SDL_RENDERER(), &outerRect);

	m_screenImage->DrawNoCamOffset();
	returnText.render(400 - (returnText.getWidth() / 2), 600 - (returnText.getHeight()));

	Renderer::GetInstance()->RenderScreen();
}

int Tutorial::Update()
{
	// Start timer if not already started
	if (!timer->isStarted())
	{
		timer->start();
	}

	// Left arrow key
	if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_LEFT) && timer->getTicks()/1000 > 0)
	{
		if (screenNo > 1)
		{
			screenNo -= 1;
			loadTTFMedia();
		}
		timer->reset();
	}

	// Right arrow key
	if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_RIGHT) && timer->getTicks() / 1000 > 0)
	{
		if (screenNo < 10)
		{
			screenNo += 1;
			loadTTFMedia();
		}
		timer->reset();
	}

	// Go back to main menu
	if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_RETURN) || KeyBoardInput::GetInstance()->isKeyPressed(SDLK_ESCAPE))
	{
		screenNo = 0;
		return MAIN_MENU;
	}

	// Left Arrow
	if (screenNo > 1)
	{
		m_drawLeftArrow = true;
	}
	else
	{
		m_drawLeftArrow = false;
	}

	// Right Arrow
	if (screenNo < 10)
	{
		m_drawRightArrow = true;
	}
	else
	{
		m_drawRightArrow = false;
	}
	return 0;
}