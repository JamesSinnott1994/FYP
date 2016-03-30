#include "stdafx.h"
#include "Menu.h"

Menu::Menu(int windowWidth, int windowHeight)
{
	// Create background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/MainMenuBackground.png",
		SDL_Rect{ windowWidth / 2, windowHeight / 2, windowWidth, windowHeight }, SDL_Rect{ 0, 0, 1280, 960 });
	m_backGroundImage->SetOffset(SDL_Point{ windowWidth / 2, windowHeight / 2 });

	// Create Play button
	float playBtnWidth = 167;
	float playBtnHeight = 144;
	float playBtnXPos = windowWidth / 2 - (playBtnWidth / 2);
	float playBtnYPos = windowHeight - playBtnHeight;
	m_playButton.Init(SDL_Rect{ playBtnXPos, playBtnYPos, playBtnWidth, playBtnHeight },
		SDL_Rect{ 0, 0, 167, 144 }, "Images/PlayBtnNotOver.png");

	// Create Options button
	float optionsBtnWidth = 229;
	float optionsBtnHeight = 62;
	float optionsBtnXPos = windowWidth / 5 - (optionsBtnWidth / 2);
	float optionsBtnYPos = windowHeight - optionsBtnHeight;
	m_optionsButton.Init(SDL_Rect{ optionsBtnXPos, optionsBtnYPos, optionsBtnWidth, optionsBtnHeight },
		SDL_Rect{ 0, 0, 229, 62 }, "Images/OptionsBtnNotOver.png");

	// Create Exit button
	float exitBtnWidth = 127;
	float exitBtnHeight = 62;
	float exitBtnXPos = windowWidth - (exitBtnWidth * 2);
	float exitBtnYPos = windowHeight - exitBtnHeight;
	m_exitButton.Init(SDL_Rect{ exitBtnXPos, exitBtnYPos, exitBtnWidth, exitBtnHeight },
		SDL_Rect{ 0, 0, 127, 62 }, "Images/ExitBtnNotOver.png");

	// Prevents constant draw when over buttons
	m_playImageOver = false;
	m_optionsImageOver = false;
	m_exitImageOver = false;
}

void Menu::Draw()
{
	Renderer::GetInstance()->ClearRenderer();
	m_backGroundImage->DrawNoCamOffset();
	m_playButton.Draw();
	m_optionsButton.Draw();
	m_exitButton.Draw();
	Renderer::GetInstance()->RenderScreen();
}

int Menu::Update(SDL_Event e)
{
	SoundManager::GetInstance()->play(SoundManager::GetInstance()->MENU_MUSIC);

	#pragma region Mouseover

	// Checks if mouse is over Play button
	#pragma region PlayButton
	if (m_playButton.IsOver(e.button.x, e.button.y))
	{
		if (!m_playImageOver)
		{
			m_playButton.Init(SDL_Rect{ m_playButton.GetRectangle().x, m_playButton.GetRectangle().y, m_playButton.GetRectangle().w, m_playButton.GetRectangle().h },
				SDL_Rect{ 0, 0, m_playButton.GetRectangle().w, m_playButton.GetRectangle().h }, "Images/PlayBtnOver.png");
		}
		m_playImageOver = true;
	}
	else
	{
		if (m_playImageOver)
		{
			m_playButton.Init(SDL_Rect{ m_playButton.GetRectangle().x, m_playButton.GetRectangle().y, m_playButton.GetRectangle().w, m_playButton.GetRectangle().h },
				SDL_Rect{ 0, 0, m_playButton.GetRectangle().w, m_playButton.GetRectangle().h }, "Images/PlayBtnNotOver.png");
		}
		m_playImageOver = false;
	}
	#pragma endregion


	// Checks if mouse is over Options button
	#pragma region OptionsButton
	if (m_optionsButton.IsOver(e.button.x, e.button.y))
	{
		if (!m_optionsImageOver)
		{
			m_optionsButton.Init(SDL_Rect{ m_optionsButton.GetRectangle().x, m_optionsButton.GetRectangle().y, m_optionsButton.GetRectangle().w, m_optionsButton.GetRectangle().h },
				SDL_Rect{ 0, 0, m_optionsButton.GetRectangle().w, m_optionsButton.GetRectangle().h }, "Images/OptionsBtnOver.png");
		}
		m_optionsImageOver = true;
	}
	else
	{
		if (m_optionsImageOver)
		{
			m_optionsButton.Init(SDL_Rect{ m_optionsButton.GetRectangle().x, m_optionsButton.GetRectangle().y, m_optionsButton.GetRectangle().w, m_optionsButton.GetRectangle().h },
				SDL_Rect{ 0, 0, m_optionsButton.GetRectangle().w, m_optionsButton.GetRectangle().h }, "Images/OptionsBtnNotOver.png");
		}
		m_optionsImageOver = false;
	}
	#pragma endregion


	// Checks if mouse is over Exit button
	#pragma region ExitButton
	if (m_exitButton.IsOver(e.button.x, e.button.y))
	{
		if (!m_exitImageOver)
		{
			m_exitButton.Init(SDL_Rect{ m_exitButton.GetRectangle().x, m_exitButton.GetRectangle().y, m_exitButton.GetRectangle().w, m_exitButton.GetRectangle().h },
				SDL_Rect{ 0, 0, m_exitButton.GetRectangle().w, m_exitButton.GetRectangle().h }, "Images/ExitBtnOver.png");
		}
		m_exitImageOver = true;
	}
	else
	{
		if (m_exitImageOver)
		{
			m_exitButton.Init(SDL_Rect{ m_exitButton.GetRectangle().x, m_exitButton.GetRectangle().y, m_exitButton.GetRectangle().w, m_exitButton.GetRectangle().h },
				SDL_Rect{ 0, 0, m_exitButton.GetRectangle().w, m_exitButton.GetRectangle().h }, "Images/ExitBtnNotOver.png");
		}
		m_exitImageOver = false;
	}
	#pragma endregion


	#pragma endregion

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
				if (m_playButton.IsClicked(mouse_x, mouse_y))
				{
					return PLAY;
				}
				else if (m_optionsButton.IsClicked(mouse_x, mouse_y))
				{
					return OPTIONS;
				}
				else if (m_exitButton.IsClicked(mouse_x, mouse_y))
				{
					return EXIT;
				}
			}
		}

	#pragma endregion

	return MENU;
}