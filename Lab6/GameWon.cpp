#include "stdafx.h"
#include "GameWon.h"

GameWon::GameWon(int windowWidth, int windowHeight)
{
	// Create background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/Menu/GameWonScreen.png",
		SDL_Rect{ windowWidth / 2, windowHeight / 2, windowWidth, windowHeight }, SDL_Rect{ 0, 0, 3840, 2400 });
	m_backGroundImage->SetOffset(SDL_Point{ windowWidth / 2, windowHeight / 2 });

	// Create menu button
	float backMenuWidth = 191;
	float backMenuHeight = 46;
	float backMenuXPos = windowWidth * 0.1f;
	float backMenuYPos = windowHeight *0.85f;
	m_menuButton.Init(SDL_Rect{ backMenuXPos, backMenuYPos, backMenuWidth, backMenuHeight },
		SDL_Rect{ 0, 0, 191, 46 }, "Images/Menu/MainMenuNotOver.png");

	// Prevents constant draw when over buttons
	m_overMenuBtn = false;
}

void GameWon::Draw()
{
	Renderer::GetInstance()->ClearRenderer();
	m_backGroundImage->DrawNoCamOffset();
	m_menuButton.Draw();
	Renderer::GetInstance()->RenderScreen();
}

int GameWon::Update(SDL_Event e)
{
	// Checks if mouse is over Menu button
	#pragma region MenuButton
	if (m_menuButton.IsOver(e.button.x, e.button.y))
	{
		if (!m_overMenuBtn)
		{
			m_menuButton.Init(SDL_Rect{ m_menuButton.GetRectangle().x, m_menuButton.GetRectangle().y, m_menuButton.GetRectangle().w, m_menuButton.GetRectangle().h },
				SDL_Rect{ 0, 0, 191, 46 }, "Images/Menu/MainMenuOver.png");
		}
		m_overMenuBtn = true;
	}
	else
	{
		if (m_overMenuBtn)
		{
			m_menuButton.Init(SDL_Rect{ m_menuButton.GetRectangle().x, m_menuButton.GetRectangle().y, m_menuButton.GetRectangle().w, m_menuButton.GetRectangle().h },
				SDL_Rect{ 0, 0, 191, 46 }, "Images/Menu/MainMenuNotOver.png");
		}
		m_overMenuBtn = false;
	}
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
			if (m_menuButton.IsClicked(mouse_x, mouse_y))
			{
				return MENU;
			}
		}
	}
	#pragma endregion

	return 0;
}