#ifndef PLATFORMMANAGER_H
#define PLATFORMMANAGER_H

#include <list>
#include "Platform.h"
#include "MovingPlatform.h"

class PlatformManager
{
public:
	static PlatformManager* GetInstance();
	~PlatformManager()
	{
		instanceFlag = false;
	}

	void addPlatform(SDL_Rect pRect, b2World* world, string type);
	void addMovingPlatform(SDL_Rect pRect, b2World* world, string type);

	void Draw();
	void Update();
	void Destroy();

private:
	PlatformManager()
	{
		// Platforms
		m_platforms = list<Platform*>();

		// Moving platforms
		m_movingPlatforms = list<MovingPlatform*>();
	}

	static bool instanceFlag;
	static PlatformManager* instance;

	// Platforms
	list<Platform*> m_platforms;
	SDL_Texture* m_platformTexture;
	SDL_Rect m_platformSource;

	// Moving platforms
	list<MovingPlatform*> m_movingPlatforms;
	SDL_Texture* m_movingPlatformTexture;
	SDL_Rect m_movingPlatformSource;
};

#endif