#ifndef GAMEWON_H
#define GAMEWON_H

#include "Sprite.h"
#include "Button.h"
#include "KeyBoardInput.h"

class GameWon
{
private:
	Sprite* m_backGroundImage;

	// Buttons
	Button m_continueButton;

	// Prevents constant draw when over buttons
	bool m_overContinueBtn;
public:
	GameWon(int windowWidth, int windowHeight);

	void Draw();
	int Update(SDL_Event e);

	const int MENU = 1;
};

#endif