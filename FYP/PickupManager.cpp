#include "stdafx.h"
#include "PickupManager.h"

#include <fstream>

bool PickupManager::instanceFlag = false;
PickupManager* PickupManager::instance = NULL;

PickupManager* PickupManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new PickupManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void PickupManager::Init()
{
	// Need to read in scoreObject positions here
	Score score(400, 500);
	scoreObjects.push_back(score);

	Score score2(100, 100);
	scoreObjects.push_back(score2);

}

void PickupManager::Draw(sf::RenderWindow &window)
{
	for each(Score score in scoreObjects)
	{
		score.Draw(window);
	}
}

std::list<Score> PickupManager::scoreObjectList()
{
	return scoreObjects;
}

void PickupManager::Update()
{

}