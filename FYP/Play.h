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

	Level* level;
public:
	Play(b2World*,int w, int h);
	~Play(){
	}
	void Init();
	void AddAssetsToRenderer();
	void Update();
	void Draw();
	void UpdateCameraPos();

	bool initializeTTF();
	bool loadTTFMedia();
};
#endif
