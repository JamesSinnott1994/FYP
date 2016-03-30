#ifndef GAMEOVER_H
#define GAMEOVER_H

#include "Sprite.h"
#include "SoundManager.h"
#include "Timer.h"

class HighScoreScreen;

class GameOver
{
private:
	Sprite* m_backGroundImage;

	Timer* timer;
public:
	GameOver(int windowWidth, int windowHeight);

	void Draw();
	int Update(string name, HighScoreScreen* highscore, int score);

	const int MENU = 1;
};

#endif