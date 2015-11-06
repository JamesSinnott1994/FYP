#ifndef SCORE_H
#define SCORE_H

#include "stdafx.h"

class Score
{
public:
	Score(int x, int y, sf::Texture*);

	~Score();

	void Draw(sf::RenderWindow &window);

	bool getAlive();
	void setAlive(bool);

	sf::Sprite getSprite() const;

	void setTexture();
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::RectangleShape m_platformRect;

	bool m_alive;
};

#endif