#ifndef PICKUPMANAGER_H
#define PICKUPMANAGER_H

#include "Score.h"

class PickupManager
{
public:
	void Init();
	void Draw(sf::RenderWindow &window);
	void Update();

	std::list<Score> scoreObjectList();

	static PickupManager* GetInstance();

	~PickupManager()
	{
		instanceFlag = false;
	}
private:
	PickupManager()
	{
		scoreObjects = std::list<Score>();
	}
	std::list<Score> scoreObjects;
	static bool instanceFlag;
	static PickupManager* instance;
};

#endif