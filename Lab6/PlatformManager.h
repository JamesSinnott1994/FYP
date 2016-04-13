#ifndef PLATFORMMANAGER_H
#define PLATFORMMANAGER_H

#include <list>
#include <vector>
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
	void addMovingPlatform(SDL_Rect pRect, b2World* world, string type, bool pLeftRight);
	void addMovePlatSensor(SDL_Rect pRect, b2World* world, int dir);

	void Draw();
	void Update();
	void Destroy();

	bool CheckCollision(b2Body*);
	bool IsLeftRight();

	std::vector<int>CheckStaticPlatCollision(b2Body*);

	int xSpeedOfMovingPlatform;
	int ySpeedOfMovingPlatform;

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
	vector<int> platformOn;

	// Moving platforms
	list<MovingPlatform*> m_movingPlatforms;
	SDL_Texture* m_movingPlatformTexture;
	SDL_Rect m_movingPlatformSource;

	// Moving platform SENSORS
	std::list<MovingPlatform*> movingPlatformsSensors;
};

#endif