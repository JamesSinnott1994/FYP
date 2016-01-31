#ifndef GRUNTBULLET_H
#define GRUNTBULLET_H

#include "Sprite.h"

class GruntBullet
{
private:
	SDL_Rect m_rect;

	int m_width;
	int m_height;

	b2Body* myBody;
	b2BodyDef myBodyDef;
	b2FixtureDef myBodyFixtureDef;
	Sprite* sprite;
	b2PolygonShape myShape;
	SDL_Texture* myTexture;

	bool m_facingRight;

public:
	GruntBullet();
	GruntBullet(SDL_Texture* text, int width, int height, SDL_Rect pRect, b2World* wWorld, SDL_Rect src, bool facingRight);

	void Draw();
	void Update();

	bool OutOfBounds(SDL_Rect &gruntRect);
};

#endif