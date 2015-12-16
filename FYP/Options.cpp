#include "stdafx.h"
#include "Options.h"

Options::Options(int windowWidth, int windowHeight)
{
	// Create background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/MainMenuBackground.png",
		SDL_Rect{ windowWidth / 2, windowHeight / 2, windowWidth, windowHeight }, SDL_Rect{ 0, 0, 1280, 960 });
	m_backGroundImage->SetOffset(SDL_Point{ windowWidth / 2, windowHeight / 2 });

	// Create back button
	float playBtnWidth = 100;
	float playBtnHeight = 33;
	float playBtnXPos = windowWidth - (playBtnWidth);
	float playBtnYPos = windowHeight - playBtnHeight;
	m_backButton.Init(SDL_Rect{ playBtnXPos, playBtnYPos, playBtnWidth, playBtnHeight },
		SDL_Rect{ 0, 0, 167, 144 }, "Images/Back.png");
}

void Options::Draw()
{
	Renderer::GetInstance()->ClearRenderer();
	m_backGroundImage->DrawNoCamOffset();
	m_backButton.Draw();
	Renderer::GetInstance()->RenderScreen();
}

int Options::Update(SDL_Event e)
{
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
		}
	}

#pragma endregion

	return OPTIONS;
}