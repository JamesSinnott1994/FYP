#include "stdafx.h"
#include "Player.h"

Player::Player(int windowWidth, int windowHeight)
{
	//m_texture.loadFromFile("Images/spritesheet1.png");
	m_texture.loadFromFile("Images/doublespritesheet.png");

	// set up the animations for all four directions (set spritesheet and push frames)

	m_walkingAnimationRight.setSpriteSheet(m_texture);
	m_walkingAnimationRight.addFrame(sf::IntRect(0, 0, 76, 107));
	m_walkingAnimationRight.addFrame(sf::IntRect(90, 0, 69, 107));
	m_walkingAnimationRight.addFrame(sf::IntRect(175, 0, 75, 107));
	m_walkingAnimationRight.addFrame(sf::IntRect(264, 0, 84, 107));
	m_walkingAnimationRight.addFrame(sf::IntRect(362, 0, 87, 107));
	m_walkingAnimationRight.addFrame(sf::IntRect(465, 0, 74, 107));
	m_walkingAnimationRight.addFrame(sf::IntRect(555, 0, 70, 107));
	m_walkingAnimationRight.addFrame(sf::IntRect(638, 0, 73, 107));
	m_walkingAnimationRight.addFrame(sf::IntRect(719, 0, 83, 107));
	m_walkingAnimationRight.addFrame(sf::IntRect(826, 0, 84, 107));

	m_walkingAnimationLeft.setSpriteSheet(m_texture);
	m_walkingAnimationLeft.addFrame(sf::IntRect(913, 107, -76, 107));
	m_walkingAnimationLeft.addFrame(sf::IntRect(822, 107, -69, 107));
	m_walkingAnimationLeft.addFrame(sf::IntRect(736, 107, -75, 107));
	m_walkingAnimationLeft.addFrame(sf::IntRect(646, 107, -84, 107));
	m_walkingAnimationLeft.addFrame(sf::IntRect(548, 107, -87, 107));
	m_walkingAnimationLeft.addFrame(sf::IntRect(446, 107, -74, 107));
	m_walkingAnimationLeft.addFrame(sf::IntRect(354, 107, -70, 107));
	m_walkingAnimationLeft.addFrame(sf::IntRect(272, 107, -73, 107));
	m_walkingAnimationLeft.addFrame(sf::IntRect(192, 107, -83, 107));
	m_walkingAnimationLeft.addFrame(sf::IntRect(84, 107, -84, 107));

	m_currentAnimation = &m_walkingAnimationRight;

	m_animationSpeed = 80.f;
	m_noKeyWasPressed = true;

	sf::Vector2i screenDimensions = sf::Vector2i(windowWidth, windowHeight);

	// Initialize AnimatedSprite
	m_animatedSprite = new AnimatedSprite(sf::seconds(0.2), true, false);
	m_animatedSprite->setPosition(sf::Vector2f(50, 50));

	m_animatedSprite->setScale(0.75f, 0.75f);

	m_animatedSprite->setAnimation(*m_currentAnimation);

	m_animatedSprite->setPosition(sf::Vector2f(m_animatedSprite->getGlobalBounds().width, windowHeight - (m_animatedSprite->getGlobalBounds().height+22)));

	//std::cout << m_animatedSprite->getGlobalBounds().width << std::endl;
	//std::cout << m_animatedSprite->getGlobalBounds().height << std::endl;
}

void Player::Update(sf::Event Event)
{
	sf::Time frameTime = m_frameClock.restart();

	// if a key was pressed set the correct animation and move correctly
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_currentAnimation = &m_walkingAnimationLeft;
		movement.x -= m_animationSpeed;
		m_noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_currentAnimation = &m_walkingAnimationRight;
		movement.x += m_animationSpeed;
		m_noKeyWasPressed = false;
	}
	m_animatedSprite->play(*m_currentAnimation);
	m_animatedSprite->move(movement * frameTime.asSeconds());

	// if no key was pressed stop the animation
	if (m_noKeyWasPressed)
	{
		m_animatedSprite->stop();
	}
	m_noKeyWasPressed = true;

	// update AnimatedSprite
	m_animatedSprite->update(frameTime);
}

void Player::Draw(sf::RenderWindow &window)
{
	window.draw(*m_animatedSprite);
}