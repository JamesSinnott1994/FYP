#include "stdafx.h"
#include "Level.h"

Level::Level(std::string levelNum)
{
	// Load platforms for the specific level
	PlatformManager::GetInstance()->Init();
}

void Level::Draw(sf::RenderWindow &window)
{
	PlatformManager::GetInstance()->Draw(window);
}