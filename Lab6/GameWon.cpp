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
	float backContinueWidth = 191;
	float backContinueHeight = 46;
	float backContinueXPos = windowWidth * 0.1f;
	float backContinueYPos = windowHeight *0.85f;
	m_continueButton.Init(SDL_Rect{ backContinueXPos, backContinueYPos, backContinueWidth, backContinueHeight },
		SDL_Rect{ 0, 0, 191, 46 }, "Images/Menu/ContinueBtnNotOver.png");

	// Prevents constant draw when over buttons
	m_overContinueBtn = false;

	// Boolean to prevent constantly adding to database
	scoreAddedToDatabase = false;
}

void GameWon::Draw()
{
	Renderer::GetInstance()->ClearRenderer();
	m_backGroundImage->DrawNoCamOffset();
	m_continueButton.Draw();
	Renderer::GetInstance()->RenderScreen();
}

int GameWon::Update(SDL_Event e, bool highscoreEnabled, string name, HighScoreScreen* highscore, int score)
{
	SoundManager::GetInstance()->play(SoundManager::GetInstance()->VICTORY);

	if (highscoreEnabled && !scoreAddedToDatabase)
	{
		highscore->PostServerData(name, score);
		scoreAddedToDatabase = true;
	}

	// Checks if mouse is over Menu button
	#pragma region MenuButton
	if (m_continueButton.IsOver(e.button.x, e.button.y))
	{
		if (!m_overContinueBtn)
		{
			m_continueButton.Init(SDL_Rect{ m_continueButton.GetRectangle().x, m_continueButton.GetRectangle().y, m_continueButton.GetRectangle().w, m_continueButton.GetRectangle().h },
				SDL_Rect{ 0, 0, 191, 46 }, "Images/Menu/ContinueBtnOver.png");
		}
		m_overContinueBtn = true;
	}
	else
	{
		if (m_overContinueBtn)
		{
			m_continueButton.Init(SDL_Rect{ m_continueButton.GetRectangle().x, m_continueButton.GetRectangle().y, m_continueButton.GetRectangle().w, m_continueButton.GetRectangle().h },
				SDL_Rect{ 0, 0, 191, 46 }, "Images/Menu/ContinueBtnNotOver.png");
		}
		m_overContinueBtn = false;
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
			if (m_continueButton.IsClicked(mouse_x, mouse_y))
			{
				if (!highscoreEnabled)
					SoundManager::GetInstance()->stopMusic();
				return MENU;
			}
		}
	}
	#pragma endregion

	return 0;
}

void GameWon::SetScoreAddedToDatabase(bool myScoreAddedToDatabase)
{
	scoreAddedToDatabase = myScoreAddedToDatabase;
}