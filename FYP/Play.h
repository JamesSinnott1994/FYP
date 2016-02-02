#ifndef _PLAY_H_
#define _PLAY_H_

#include <iostream>
#include <stdio.h>

#include <SDL.h>
#include <Box2D/Box2D.h>
#include <KeyBoardInput.h>
#include "Player.h"
#include "Sprite.h"
#include "Level.h"
#include "PickupManager.h"
#include "HealthBar.h"
#include "Teleporter.h"
#include "Timer.h"
#include "InGameMenu.h"

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "Text.h"

class Play
{
private:
	b2World* world;
	Player* m_player;
	int framecounter;
	bool playerDead;
	bool levelComplete;

	Sprite* m_backGroundImage;

	HealthBar* m_healthBar;

	//Globally used font
	TTF_Font *gFont = NULL;

	//Rendered texture
	Text gScoreTextTexture;
	Text gLevelTextTexture;

	// Different speeds
	float labComputerSpeed;
	float laptopSpeed;
	float speedToUse;

	// Screen width and height
	int m_width;
	int m_height;

	Level* level;

	// Timer
	Timer* timer;

	string whichSpeed;

	// Menu
	bool menuOpen;
	bool paused;

public:
	Play(b2World*, int w, int h);
	~Play(){}

	void Init(b2World*, int w, int h);
	void AddAssetsToRenderer();
	int Update(SDL_Event e);
	void Reset();
	void Quit();
	void Draw();
	void LevelComplete();
	void UpdateCameraPos();

	bool initializeTTF();
	bool loadTTFMedia();
};
#endif
