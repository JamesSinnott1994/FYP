#ifndef SCORE2_H
#define SCORE2_H

#include "stdafx.h"

class Score2
{
public:
	Score2(int, int);

	void Draw(sf::RenderWindow &window);

	bool getAlive();
	void setAlive(bool);

	sf::Sprite getSprite() const;
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	bool m_alive;
};

#endif