#ifndef OPTIONS_H
#define OPTIONS_H

#include "Sprite.h"
#include "Button.h"

class Options
{
public:
	Options(int, int);

	void Draw();
	int Update(SDL_Event e);

	// Options states for buttons
	const int OPTIONS = 0;
	const int MENU = 1;
private:
	Sprite* m_backGroundImage;

	Button m_backButton;
};

#endif