#include "stdafx.h"
#include "Instructions.h"

Instructions::Instructions(int windowWidth, int windowHeight)
{
	// Create background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/space.png",
		SDL_Rect{ windowWidth / 2, windowHeight / 2, windowWidth, windowHeight }, SDL_Rect{ 0, 0, 1280, 960 });
	m_backGroundImage->SetOffset(SDL_Point{ windowWidth / 2, windowHeight / 2 });

	initializeTTF();
	loadTTFMedia();
}

bool Instructions::initializeTTF()
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

bool Instructions::loadTTFMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("Font/ARDESTINE.ttf", 20);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 165, 0 };
		if (!moveText.loadFromRenderedText("Use left and right arrows or 'A' and 'D' keys to move player", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!jumpText.loadFromRenderedText("Press 'Spacebar' to jump", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!shootText.loadFromRenderedText("Press 'J' key to shoot", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
		if (!enterText.loadFromRenderedText("-> Enter to continue <-", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void Instructions::Draw()
{
	Renderer::GetInstance()->ClearRenderer();
	m_backGroundImage->DrawNoCamOffset();
	// Draw text at position
	moveText.render(85, 100);
	jumpText.render(85, 200);
	shootText.render(85, 300);
	enterText.render(moveText.getWidth() / 2, 500);
	Renderer::GetInstance()->RenderScreen();
}

int Instructions::Update()
{
	if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_RETURN))
	{
		return 1;
	}
	return 0;
}