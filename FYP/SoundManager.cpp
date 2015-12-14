#include "stdafx.h"
#include <SoundManager.h>


bool SoundManager::instanceFlag = false;
SoundManager* SoundManager::instance = NULL;

SoundManager* SoundManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new SoundManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

bool SoundManager::load_files()
{
	// Load sound effects
	scorePickup = Mix_LoadWAV("Sound/Pickup.wav");
	gunshot = Mix_LoadWAV("Sound/Gunshot.wav");
	health = Mix_LoadWAV("Sound/Health.wav");

	//If there was a problem loading the sound effects
	if (scorePickup == NULL || gunshot == NULL || health == NULL)
	{
		return false;
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME / 10);//music volume
	Mix_Volume(-1, MIX_MAX_VOLUME / 2);//set volume for all sound effects

	//If everything loaded fine
	return true;
}
void SoundManager::clean_up()
{
	//Free the sound effects
	Mix_FreeChunk(scorePickup);

	//Quit SDL_mixer
	Mix_CloseAudio();

	//Quit SDL
	SDL_Quit();
}
void SoundManager::play(int i)
{
	//If there is no music playing
	switch (i)
	{
	case SCORE_PICKUP:
		Mix_PlayChannel(SCORE_PICKUP, scorePickup, 0);
		break;
	case GUNSHOT:
		Mix_PlayChannel(GUNSHOT, gunshot, 0);
		break;
	case HEALTH:
		Mix_PlayChannel(HEALTH, health, 0);
		break;
	}
}
void SoundManager::stopMusic()
{
	//Stop the music
	Mix_HaltMusic();
}
