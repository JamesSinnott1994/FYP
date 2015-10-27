#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedSprite.h"

class Player
{
public:
	Player(int windowWidth, int windowHeight);

	void Update(sf::Event Event);
	void Draw(sf::RenderWindow &window);
private:
	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::Texture m_texture;

	Animation m_walkingAnimationDown;
	Animation m_walkingAnimationLeft;
	Animation m_walkingAnimationRight;
	Animation m_walkingAnimationUp;

	Animation* m_currentAnimation;

	AnimatedSprite* m_animatedSprite;

	float m_animationSpeed;
	bool m_noKeyWasPressed;

	sf::Clock m_frameClock;
};

#endif