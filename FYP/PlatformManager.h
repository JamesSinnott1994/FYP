#ifndef PLATFORMMANAGER_H
#define PLATFORMMANAGER_H

#include "Platform.h"

class PlatformManager
{
public:
	void Init();
	void Draw(sf::RenderWindow &window);
	void Update();

	static PlatformManager* GetInstance();

	std::list<Platform> platformObjectList();

	~PlatformManager()
	{
		instanceFlag = false;
	}
private:
	PlatformManager()
	{
		platforms = std::list<Platform>();
	}
	std::list<Platform> platforms;
	static bool instanceFlag;
	static PlatformManager* instance;
};

#endif