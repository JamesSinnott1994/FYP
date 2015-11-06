#include "stdafx.h"
#include "Score.h"

Score::Score(int x, int y, sf::Texture* texture)
{
	//sf::Texture pTexture;
	//pTexture.loadFromFile("Images/Coin.png");
	//m_texture.loadFromFile("Images/Coin.png");

	//m_sprite.setTexture(m_texture);

	sf::Texture texture2;
	if (!m_texture.loadFromFile("Images/Coin.png"))
	{
		std::cout << "Error!!!" << std::endl;
	}

	m_sprite.setTexture(*texture);

	m_sprite.setScale(0.25f, 0.25f);

	m_sprite.setPosition(sf::Vector2f(x, y));

	std::cout << m_texture.getSize().x << std::endl;


	std::cout << "X Pos: " << m_sprite.getGlobalBounds().left << std::endl;
	std::cout << "Y Pos: " << m_sprite.getGlobalBounds().top << std::endl;
	std::cout << "Width: " << m_sprite.getGlobalBounds().width << std::endl;
	std::cout << "Height: " << m_sprite.getGlobalBounds().height << std::endl;
	std::cout << std::endl;

	std::cout << "X Pos: " << m_sprite.getLocalBounds().left << std::endl;
	std::cout << "Y Pos: " << m_sprite.getLocalBounds().top << std::endl;
	std::cout << "Width: " << m_sprite.getLocalBounds().width << std::endl;
	std::cout << "Height: " << m_sprite.getLocalBounds().height << std::endl;

	m_alive = true;
}

Score::~Score()
{
	
}

void Score::Draw(sf::RenderWindow &window)
{
	sf::Texture pTexture;
	pTexture.loadFromFile("Images/Coin.png");

	m_sprite.setTexture(pTexture);

	if (getAlive())
		window.draw(getSprite());

	//// Create a sprite
	//sf::RectangleShape rect;
	//rect.setPosition(sf::Vector2f(m_sprite.getPosition().x, m_sprite.getPosition().y));
	//rect.setSize(sf::Vector2f(m_sprite.getGlobalBounds().width, m_sprite.getGlobalBounds().height));
	//rect.setFillColor(sf::Color(255, 255, 255, 200));
	//window.draw(rect);

	//std::cout << "Width: " << m_sprite.getGlobalBounds().width << std::endl;
}

bool Score::getAlive()
{
	return m_alive;
}

void Score::setAlive(bool myAlive)
{
	m_alive = myAlive;
}

sf::Sprite Score::getSprite() const
{
	return m_sprite;
}

void Score::setTexture()
{
	sf::Texture pTexture;
	pTexture.loadFromFile("Images/Coin.png");

	m_sprite.setTexture(pTexture);
}