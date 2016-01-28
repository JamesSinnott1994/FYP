#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <iostream> 
#include <SDL.h>			//SDL
#include <stdio.h>
#include "SDL_mixer.h"
#include <list>

#pragma comment(lib, "SDL2_mixer.lib")

using namespace std;

class EnemyManager
{
public:
	static EnemyManager* GetInstance();
	~EnemyManager()
	{
		instanceFlag = false;
	}
private:
	EnemyManager()
	{

	}

	static bool instanceFlag;
	static EnemyManager* instance;

};
#endif