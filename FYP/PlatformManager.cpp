#include "stdafx.h"
#include "PlatformManager.h"

#include <fstream>

bool PlatformManager::instanceFlag = false;
PlatformManager* PlatformManager::instance = NULL;

PlatformManager* PlatformManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new PlatformManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void PlatformManager::Init()
{
	// Need to read in platform positions here

	// For reading from text file
	std::ifstream myFile;

	// Position for nodes
	int xPos = 0;
	int yPos = 0;
	int width = 0;
	int height = 0;

	myFile.open("Text/PlatformsLevelOne.txt");
	while (myFile >> xPos >> yPos >> width >> height)
	{
		Platform platform(xPos, yPos, width, height);
		platforms.push_back(platform);
	}
	myFile.close();

}

void PlatformManager::Draw(sf::RenderWindow &window)
{
	for each(Platform plat in platforms)
	{
		plat.Draw(window);
	}
}

void PlatformManager::Update()
{

}

std::list<Platform> PlatformManager::platformObjectList()
{
	return platforms;
}