#ifndef SPLASH_H
#define SPLASH_H

#include "Sprite.h"
#include "KeyBoardInput.h"
#include "Text.h"

class Instructions
{
public:
	Instructions(int, int);

	void Draw();
	int Update();

	// Used for drawing text
	bool initializeTTF();
	bool loadTTFMedia();
private:
	Sprite* m_backGroundImage;

	//Globally used font
	TTF_Font *gFont = NULL;

	//Rendered texture
	Text moveText;
	Text jumpText;
	Text shootText;
	Text enterText;
	Text menuText;
};

#endif