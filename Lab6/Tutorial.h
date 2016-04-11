#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Sprite.h"
#include "KeyBoardInput.h"
#include "Text.h"
#include "Timer.h"

class Tutorial
{
private:
	Sprite* m_backGroundImage;
	Sprite* m_screenImage;
	Sprite* m_leftArrow;
	Sprite m_rightArrow;

	//Globally used font
	TTF_Font *gFont = NULL;
	TTF_Font *gFont2 = NULL;

	//Rendered texture
	Text returnText;

	// Screens
	int screenNo;

	// Timer
	Timer* timer;

	// States
	const int MAIN_MENU = 1;
public:
	Tutorial();
	Tutorial(int windowWidth, int windowHeight);

	void Draw();
	int Update();

	// Used for drawing text
	bool initializeTTF();
	bool loadTTFMedia();
};

#endif