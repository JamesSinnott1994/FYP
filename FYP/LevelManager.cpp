#include "stdafx.h"
#include "LevelManager.h"

bool LevelManager::instanceFlag = false;
LevelManager* LevelManager::instance = NULL;

LevelManager* LevelManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new LevelManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void LevelManager::Init()
{
	Level levelOne("LevelOne");

	levels.push_back(levelOne);
}

void LevelManager::Draw(sf::RenderWindow &window)
{
	for each(Level level in levels)
	{
		level.Draw(window);
	}
}

void LevelManager::Update()
{

}