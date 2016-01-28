#include "stdafx.h"
#include <EnemyManager.h>


bool EnemyManager::instanceFlag = false;
EnemyManager* EnemyManager::instance = NULL;

EnemyManager* EnemyManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new EnemyManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}