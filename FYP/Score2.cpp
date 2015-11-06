#include "stdafx.h"
#include "Score2.h"

Score2::Score2(int x, int y)
{
	if (!m_texture.loadFromFile("Images/Coin.png"))
	{
		std::cout << "Error!!!" << std::endl;
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setScale(0.25f, 0.25f);
	m_sprite.setPosition(sf::Vector2f(x, y));

	m_alive = true;
}

void Score2::Draw(sf::RenderWindow &window)
{
	if (getAlive())
		window.draw(m_sprite);
}

bool Score2::getAlive()
{
	return m_alive;
}

void Score2::setAlive(bool myAlive)
{
	m_alive = myAlive;
}

sf::Sprite Score2::getSprite() const
{
	return m_sprite;
}