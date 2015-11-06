#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedSprite.h"

class Player
{
public:
	Player(int windowWidth, int windowHeight);

	void Update(sf::Event Event);
	void Draw(sf::RenderWindow &window);

	AnimatedSprite* getSprite();

	bool getCollidingWithPlatform();
	void setCollidingWithPlatform(bool);

	bool getOnTopOfPlatform();
	void setOnTopOfPlatform(bool);

	int getScore();
	void setScore(int);
private:
	bool collidingWithPlatform;

	bool onTopOfPlatform;

	int score;

	sf::Vector2f position;
	sf::Vector2f velocity;

	sf::Texture m_texture;
	sf::Texture m_texture2;

	Animation m_walkingAnimationDown;
	Animation m_walkingAnimationLeft;
	Animation m_walkingAnimationRight;
	Animation m_jumpAnimation;
	
	Animation* m_currentAnimation;

	AnimatedSprite* m_animatedSprite;

	float m_animationSpeed;
	bool m_noKeyWasPressed;

	bool m_jumpKeyPressed;
	float yVelocity;

	int time;
	int timer;

	sf::Clock m_frameClock;
};

#endif