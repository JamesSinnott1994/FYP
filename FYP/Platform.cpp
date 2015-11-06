#include "stdafx.h"
#include "Platform.h"

Platform::Platform(int x, int y, int width, int height)
{
	sf::Texture pTexture;
	pTexture.loadFromFile("Images/platform.png");

	////////////////////

	m_platformRect.setPosition(sf::Vector2f(x, y));

	m_platformRect.setSize(sf::Vector2f(width, height));

	m_platformRect.setOutlineThickness(3);

	m_platformRect.setOutlineColor(sf::Color::Black);

	//m_platformRect.setFillColor(sf::Color(100, 100, 200));

	m_platformRect.setTexture(&pTexture);
}

void Platform::Draw(sf::RenderWindow &window)
{
	sf::Texture pTexture;
	pTexture.loadFromFile("Images/platform.png");

	m_platformRect.setTexture(&pTexture);

	window.draw(m_platformRect);

	//// Create a sprite
	//sf::RectangleShape rect;
	//rect.setPosition(sf::Vector2f(m_platformRect.getPosition().x, m_platformRect.getPosition().y));
	//rect.setSize(sf::Vector2f(m_platformRect.getSize().x, m_platformRect.getSize().y));
	//rect.setFillColor(sf::Color(255, 255, 255, 200));
	//window.draw(rect);
}

sf::RectangleShape Platform::getRectangle()
{
	return m_platformRect;
}