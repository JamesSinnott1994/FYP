#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Sprite.h"
#include "KeyBoardInput.h"
#include "Text.h"

class Tutorial
{
private:
	Sprite* m_backGroundImage;

	//Globally used font
	TTF_Font *gFont = NULL;
public:
	Tutorial();
	Tutorial(int windowWidth, int windowHeight);

	void Draw();
	void Update();

	// Used for drawing text
	bool initializeTTF();
	bool loadTTFMedia();
};

#endif