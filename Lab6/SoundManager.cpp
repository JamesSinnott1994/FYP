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
	// Music
	menuMusic = Mix_LoadMUS("Sound/EvilGenius.wav");
	levelTwoMusic = Mix_LoadMUS("Sound/VelocityX.wav");

	// Load sound effects
	scorePickup = Mix_LoadWAV("Sound/Pickup.wav");
	gunshot = Mix_LoadWAV("Sound/Gunshot.wav");
	health = Mix_LoadWAV("Sound/Health.wav");
	mine = Mix_LoadWAV("Sound/MineExplosion.wav");
	electrocuted = Mix_LoadWAV("Sound/Electrocuted.wav");
	gunPickup = Mix_LoadWAV("Sound/GunPickup.wav");

	//If there was a problem loading the sound effects
	if (scorePickup == NULL || gunshot == NULL || health == NULL || mine == NULL || menuMusic == NULL
		|| levelTwoMusic == NULL || electrocuted == NULL || gunPickup == NULL)
	{
		return false;
	}
	Mix_VolumeMusic(MIX_MAX_VOLUME / 3);//music volume
	Mix_Volume(-1, MIX_MAX_VOLUME / 3);//set volume for all sound effects

	//If everything loaded fine
	return true;
}

void SoundManager::clean_up()
{
	//Free the sound effects
	Mix_FreeChunk(scorePickup);
	Mix_FreeChunk(gunshot);
	Mix_FreeChunk(health);
	Mix_FreeChunk(mine);
	Mix_FreeChunk(electrocuted);
	Mix_FreeChunk(gunPickup);

	//Free the music
	Mix_FreeMusic(menuMusic);
	Mix_FreeMusic(levelTwoMusic);

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
	case GUN_PICKUP:
		Mix_PlayChannel(GUN_PICKUP, gunPickup, 0);
		break;
	case SCORE_PICKUP:
		Mix_PlayChannel(SCORE_PICKUP, scorePickup, 0);
		break;
	case GUNSHOT:
		Mix_PlayChannel(GUNSHOT, gunshot, 0);
		break;
	case HEALTH:
		Mix_PlayChannel(HEALTH, health, 0);
		break;
	case MINE:
		Mix_PlayChannel(MINE, mine, 0);
		break;
	case ELECTROCUTED:
		Mix_PlayChannel(ELECTROCUTED, electrocuted, 0);
		break;
	case MENU_MUSIC:
		// If there is no music playing
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(menuMusic, -1);// -1 means we want it to loop until it is stopped

		}
		// If the music is being played
		else
		{
			//If the music is paused
			if (Mix_PausedMusic() == 1 && SoundOn())
			{
				//Resume the music
				Mix_ResumeMusic();
			}
			//If the music is playing
			else
			{
				if (!SoundOn())
				{
					//Pause the music
					Mix_PauseMusic();
				}
			}
		}
		break;
	case LEVEL_TWO_MUSIC:
		if (Mix_PlayingMusic() == 0)
		{
			//Play the music
			Mix_PlayMusic(levelTwoMusic, -1);

		}

		else
		{
			//If the music is paused
			if (Mix_PausedMusic() == 1 && SoundOn())
			{
				//Resume the music
				Mix_ResumeMusic();
			}
			//If the music is playing
			else
			{
				if (!SoundOn())
				{
					//Pause the music
					Mix_PauseMusic();
				}
			}
		}
		break;
	}
}

void SoundManager::stopMusic()
{
	//Stop the music
	Mix_HaltMusic();
}

bool SoundManager::SoundOn()
{
	return m_soundOn;
}

void SoundManager::SetSoundOn(bool mySound)
{
	m_soundOn = mySound;
}
