#include "stdafx.h"
#include "Options.h"

Options::Options(int windowWidth, int windowHeight)
{
	// Create background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/space.png",
		SDL_Rect{ windowWidth / 2, windowHeight / 2, windowWidth, windowHeight }, SDL_Rect{ 0, 0, 1280, 960 });
	m_backGroundImage->SetOffset(SDL_Point{ windowWidth / 2, windowHeight / 2 });

	// Create back button
	float backBtnWidth = 169;
	float backBtnHeight = 92;
	backBtnWidth = backBtnWidth / 2;
	backBtnHeight = backBtnHeight / 2;
	float backBtnXPos = windowWidth - (backBtnWidth);
	float backBtnYPos = windowHeight - backBtnHeight;
	m_backButton.Init(SDL_Rect{ backBtnXPos, backBtnYPos, backBtnWidth, backBtnHeight },
		SDL_Rect{ 0, 0, 167, 144 }, "Images/BackButton.png");

	// Create Sound On Selected button
	float onBtnWidth = 169;
	float onBtnHeight = 92;
	onBtnWidth = onBtnWidth / 2;
	onBtnHeight = onBtnHeight / 2;
	float onBtnXPos = windowWidth / 2 - (onBtnWidth / 2);
	float onBtnYPos = (windowHeight * 0.5f) - onBtnHeight;
	m_onBtnSelected.Init(SDL_Rect{ onBtnXPos, onBtnYPos, onBtnWidth, onBtnHeight },
		SDL_Rect{ 0, 0, 167, 144 }, "Images/OnBtnSelected.png");

	// Create Sound On Not Selected button
	float onBtnWidth2 = 169;
	float onBtnHeight2 = 92;
	onBtnWidth2 = onBtnWidth2 / 2;
	onBtnHeight2 = onBtnHeight2 / 2;
	float onBtnXPos2 = windowWidth / 2 - (onBtnWidth2 / 2);
	float onBtnYPos2 = (windowHeight * 0.5f) - onBtnHeight2;
	m_onBtnNotSelected.Init(SDL_Rect{ onBtnXPos2, onBtnYPos2, onBtnWidth2, onBtnHeight2 },
		SDL_Rect{ 0, 0, 167, 144 }, "Images/OnBtnNotSelected.png");

	// Create Sound Off Selected button
	float offBtnWidth = 169;
	float offBtnHeight = 92;
	offBtnWidth = offBtnWidth / 2;
	offBtnHeight = offBtnHeight / 2;
	float offBtnXPos = (windowWidth * 0.605f) - (offBtnWidth / 2);
	float offBtnYPos = (windowHeight * 0.5f) - offBtnHeight;
	m_offBtnSelected.Init(SDL_Rect{ offBtnXPos, offBtnYPos, offBtnWidth, offBtnHeight },
		SDL_Rect{ 0, 0, 167, 144 }, "Images/OffBtnSelected.png");

	// Create Sound Off Not Selected button
	float offBtnWidth2 = 169;
	float offBtnHeight2 = 92;
	offBtnWidth2 = offBtnWidth2 / 2;
	offBtnHeight2 = offBtnHeight2 / 2;
	float offBtnXPos2 = (windowWidth * 0.605f) - (offBtnWidth2 / 2);
	float offBtnYPos2 = (windowHeight * 0.5f) - offBtnHeight2;
	m_offBtnNotSelected.Init(SDL_Rect{ offBtnXPos2, offBtnYPos2, offBtnWidth2, offBtnHeight2 },
		SDL_Rect{ 0, 0, 167, 144 }, "Images/OffBtnNotSelected.png");

	// Boolean for sound
	onBtnSelected = true;
	offBtnSelected = false;

	// Width and Height
	width = windowWidth;
	height = windowHeight;

	initializeTTF();
	loadTTFMedia();
}

bool Options::initializeTTF()
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

bool Options::loadTTFMedia()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("Font/ARDESTINE.ttf", 30);
	if (gFont == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Render text
		SDL_Color textColor = { 255, 165, 0 };
		if (!soundText.loadFromRenderedText("Sound Effects:", textColor, gFont))
		{
			printf("Failed to render text texture!\n");
			success = false;
		}
	}

	return success;
}

void Options::Draw()
{
	Renderer::GetInstance()->ClearRenderer();

	m_backGroundImage->DrawNoCamOffset();
	m_backButton.Draw();

	if (SoundManager::GetInstance()->SoundOn())
	{
		onBtnSelected = true;
		m_onBtnSelected.Draw();
		m_offBtnNotSelected.Draw();
	}
	else
	{
		onBtnSelected = false;
		m_onBtnNotSelected.Draw();
		m_offBtnSelected.Draw();
	}
	/*if (onBtnSelected)
	{
		m_onBtnSelected.Draw();
		m_offBtnNotSelected.Draw();
	}
	else
	{
		m_onBtnNotSelected.Draw();
		m_offBtnSelected.Draw();
	}*/

	soundText.render(width * 0.15f, height * 0.5f - soundText.getHeight());

	Renderer::GetInstance()->RenderScreen();
}

int Options::Update(SDL_Event e)
{
	SoundManager::GetInstance()->play(SoundManager::GetInstance()->MENU_MUSIC);

#pragma region Mousedown

	// Mousedown
	if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		//If the left mouse button was pressed
		if (e.button.button == SDL_BUTTON_LEFT)
		{
			//Get the mouse offsets
			int mouse_x = e.button.x;
			int mouse_y = e.button.y;


			// Check if button clicked
			if (m_backButton.IsClicked(mouse_x, mouse_y))
			{
				return MENU;
			}

			// Check if ON/OFF buttons are clicked
			if (onBtnSelected)
			{
				if (m_offBtnNotSelected.IsClicked(mouse_x, mouse_y))
				{
					onBtnSelected = false;
					SoundManager::GetInstance()->SetSoundOn(false);
				}
			}
			else
			{
				if (m_onBtnNotSelected.IsClicked(mouse_x, mouse_y))
				{
					onBtnSelected = true;
					SoundManager::GetInstance()->SetSoundOn(true);
				}
			}
		}
	}

#pragma endregion

	return OPTIONS;
}