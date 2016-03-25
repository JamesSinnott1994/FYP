#include "stdafx.h"
#include "GameOver.h"
#include "HighScoreScreen.h"

GameOver::GameOver(int windowWidth, int windowHeight)
{
	// Create background image
	m_backGroundImage = new Sprite();
	m_backGroundImage->Init("Images/GameOverScreen.png",
		SDL_Rect{ windowWidth / 2, windowHeight / 2, windowWidth, windowHeight }, SDL_Rect{ 0, 0, 800, 600 });
	m_backGroundImage->SetOffset(SDL_Point{ windowWidth / 2, windowHeight / 2 });

	// Timer
	timer = new Timer();
}

void GameOver::Draw()
{
	Renderer::GetInstance()->ClearRenderer();
	m_backGroundImage->DrawNoCamOffset();
	Renderer::GetInstance()->RenderScreen();
}

int GameOver::Update(string name, HighScoreScreen* highscore, int score)
{
	SoundManager::GetInstance()->play(SoundManager::GetInstance()->MENU_MUSIC);

	//highscore->PostServerData(name, score);

	// Start timer if not already started
	if (!timer->isStarted())
	{
		timer->start();
	}
	// Reset after 2 seconds
	if (timer->getTicks() / 1000 >= 4)
	{
		timer->reset();
		return MENU;
	}
	return 0;
}