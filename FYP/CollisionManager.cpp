#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

bool CollisionManager::PlayerScoreCollision()
{
	std::list<Score> scoreList = PickupManager::GetInstance()->scoreObjectList();

	for each(Score score in scoreList)
	{
		
	}
	return false;
}