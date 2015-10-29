#include "stdafx.h"
#include "Platform.h"

Platform::Platform(int x, int y, int width, int height)
{
	sf::Texture pTexture;
	pTexture.loadFromFile("Images/Button.png");

	////////////////////

	m_platformRect.setPosition(sf::Vector2f(x, y));

	m_platformRect.setSize(sf::Vector2f(width, height));

	m_platformRect.setOutlineThickness(3);

	m_platformRect.setOutlineColor(sf::Color::Black);

	m_platformRect.setFillColor(sf::Color(100, 100, 200));

	m_platformRect.setTexture(&pTexture);
}

void Platform::Draw(sf::RenderWindow &window)
{
	window.draw(m_platformRect);
}