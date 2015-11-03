#include "stdafx.h"
#include "Score.h"

Score::Score(int x, int y)
{
	//sf::Texture pTexture;
	//pTexture.loadFromFile("Images/Coin.png");

	//m_sprite.setTexture(pTexture);

	m_sprite.setScale(0.25f, 0.25f);

	m_sprite.setPosition(sf::Vector2f(x, y));
}

void Score::Draw(sf::RenderWindow &window)
{
	sf::Texture pTexture;
	pTexture.loadFromFile("Images/Coin.png");

	m_sprite.setTexture(pTexture);

	window.draw(m_sprite);
}