#ifndef LEVEL_H
#define LEVEL_H

#include "PlatformManager.h"
#include "PickupManager.h"

class Level
{
public:
	Level(std::string levelNum);

	void Draw(sf::RenderWindow &window);
private:
};

#endif