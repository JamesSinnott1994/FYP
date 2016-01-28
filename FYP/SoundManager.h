#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <iostream> 
#include <SDL.h>			//SDL
#include <stdio.h>
#include "SDL_mixer.h"
#include <list>

#pragma comment(lib, "SDL2_mixer.lib")

using namespace std;

class SoundManager
{
public:
	static const int SCORE_PICKUP = 0, GUNSHOT = 1, HEALTH = 2, MINE = 3;

	static SoundManager* GetInstance();
	void play(int);
	void stopMusic();
	bool load_files();
	void clean_up();
	~SoundManager()
	{
		instanceFlag = false;
	}

	bool SoundOn();
	void SetSoundOn(bool mySound);
private:
	SoundManager()
	{
		m_soundOn = true;

		//Initialize SDL_mixer
		if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		{
			
		}
	}
	Mix_Chunk* scorePickup = NULL;
	Mix_Chunk* gunshot = NULL;
	Mix_Chunk* health = NULL;
	Mix_Chunk* mine = NULL;

	static bool instanceFlag;
	static SoundManager* instance;
	bool m_soundOn;
	
};
#endif
