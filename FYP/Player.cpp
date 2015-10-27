#include "stdafx.h"
#include "Player.h"

Player::Player(int windowWidth, int windowHeight)
{
	m_texture.loadFromFile("Images/spritesheet1.png");

	// set up the animations for all four directions (set spritesheet and push frames)
	m_walkingAnimationDown.setSpriteSheet(m_texture);
	m_walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	m_walkingAnimationDown.addFrame(sf::IntRect(64, 0, 32, 32));
	m_walkingAnimationDown.addFrame(sf::IntRect(32, 0, 32, 32));
	m_walkingAnimationDown.addFrame(sf::IntRect(0, 0, 32, 32));

	m_walkingAnimationLeft.setSpriteSheet(m_texture);
	m_walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	m_walkingAnimationLeft.addFrame(sf::IntRect(64, 32, 32, 32));
	m_walkingAnimationLeft.addFrame(sf::IntRect(32, 32, 32, 32));
	m_walkingAnimationLeft.addFrame(sf::IntRect(0, 32, 32, 32));

	m_walkingAnimationRight.setSpriteSheet(m_texture);
	m_walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	m_walkingAnimationRight.addFrame(sf::IntRect(64, 64, 32, 32));
	m_walkingAnimationRight.addFrame(sf::IntRect(32, 64, 32, 32));
	m_walkingAnimationRight.addFrame(sf::IntRect(0, 64, 32, 32));

	m_walkingAnimationUp.setSpriteSheet(m_texture);
	m_walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	m_walkingAnimationUp.addFrame(sf::IntRect(64, 96, 32, 32));
	m_walkingAnimationUp.addFrame(sf::IntRect(32, 96, 32, 32));
	m_walkingAnimationUp.addFrame(sf::IntRect(0, 96, 32, 32));

	m_currentAnimation = &m_walkingAnimationDown;

	m_animationSpeed = 80.f;
	m_noKeyWasPressed = true;

	sf::Vector2i screenDimensions = sf::Vector2i(windowWidth, windowHeight);

	// Initialize AnimatedSprite
	m_animatedSprite = new AnimatedSprite(sf::seconds(0.2), true, false);
	m_animatedSprite->setPosition(sf::Vector2f(screenDimensions / 2));
}

void Player::Update(sf::Event Event)
{
	sf::Time frameTime = m_frameClock.restart();

	// if a key was pressed set the correct animation and move correctly
	sf::Vector2f movement(0.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_currentAnimation = &m_walkingAnimationUp;
		movement.y -= m_animationSpeed;
		m_noKeyWasPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_currentAnimation = &m_walkingAnimationDown;
		movement.y += m_animationSpeed;
		m_noKeyWasPressed = false;
	}
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