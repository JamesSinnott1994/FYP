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

class Play
{
private:
	b2World* world;
	Player* m_player;
	int framecounter;
	bool playerDead;
	bool levelComplete;

	Sprite* m_backGroundImage;
public:
	Play(b2World*,int w, int h);
	~Play(){
	}
	void Init();
	void AddAssetsToRenderer();
	void Update();
	void Draw();
	void UpdateCameraPos();
};
#endif
