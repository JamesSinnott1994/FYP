#ifndef LEVEL_H
#define LEVEL_H

#include "PlatformManager.h"
#include "PickupManager.h"

class Level
{
public:
	Level(std::string levelNum);

	Level(sf::Texture);

	void Draw(sf::RenderWindow &window);

	void DrawBackground(sf::RenderWindow &window);

	void setTexture(sf::Texture);
	sf::Texture getTexture();
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

#endif