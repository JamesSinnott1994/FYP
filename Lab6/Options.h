#ifndef OPTIONS_H
#define OPTIONS_H

#include "Sprite.h"
#include "Button.h"
#include "Text.h"
#include "SoundManager.h"

class Options
{
public:
	Options(int, int);

	void Draw();
	int Update(SDL_Event e);

	// Options states for buttons
	const int OPTIONS = 0;
	const int MENU = 1;

	// Width and Height of screen
	int width;
	int height;

	// Used for drawing text
	bool initializeTTF();
	bool loadTTFMedia();

	bool onBtnSelected;
	bool offBtnSelected;
private:
	Sprite* m_backGroundImage;

	//Globally used font
	TTF_Font *gFont = NULL;

	//Rendered texture
	Text soundText;

	Button m_onBtnSelected;
	Button m_offBtnSelected;
	Button m_onBtnNotSelected;
	Button m_offBtnNotSelected;

	Button m_backButton;
};

#endif