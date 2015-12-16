#ifndef PLATFORMMANAGER_H
#define PLATFORMMANAGER_H

#include <list>
#include "Platform.h"

class PlatformManager
{
public:
	static PlatformManager* GetInstance();
	~PlatformManager()
	{
		instanceFlag = false;
	}

	void addPlatform(SDL_Rect pRect, b2World* world, string type);

	void Draw();
	void Destroy();

private:
	PlatformManager()
	{
		m_platforms = list<Platform*>();
	}

	static bool instanceFlag;
	static PlatformManager* instance;

	list<Platform*> m_platforms;

	SDL_Texture* m_platformTexture;

	SDL_Rect m_platformSource;
};

#endif