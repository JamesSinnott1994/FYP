#include "stdafx.h"
#include "Level.h"

Level::Level(std::string levelNum)
{
	// Load platforms for the specific level
	PlatformManager::GetInstance()->Init();
	PickupManager::GetInstance()->Init();
}

Level::Level(sf::Texture texture)
{
	m_texture = texture;
	setTexture(m_texture);

	m_sprite.setTexture(m_texture);

	// Scale image to window
	m_sprite.setScale(800 / m_sprite.getLocalBounds().width,
		600 / m_sprite.getLocalBounds().height);
}

void Level::Draw(sf::RenderWindow &window)
{
	PlatformManager::GetInstance()->Draw(window);
	PickupManager::GetInstance()->Draw(window);
}

void Level::DrawBackground(sf::RenderWindow &window)
{
	window.draw(m_sprite);
}

void Level::setTexture(sf::Texture myTexture)
{
	m_texture = myTexture;
}
sf::Texture Level::getTexture()
{
	return m_texture;
}