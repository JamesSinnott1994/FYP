#ifndef PLATFORM_H
#define PLATFORM_H

#include "Platform.h"

class Platform
{
public:
	Platform(int x, int y, int width, int height);

	void Draw(sf::RenderWindow &window);
private:
	sf::RectangleShape m_platformRect;
};

#endif