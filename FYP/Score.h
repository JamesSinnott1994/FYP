#ifndef SCORE_H
#define SCORE_H

#include "stdafx.h"

class Score
{
public:
	Score(int x, int y);

	void Draw(sf::RenderWindow &window);
private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	sf::RectangleShape m_platformRect;
};

#endif