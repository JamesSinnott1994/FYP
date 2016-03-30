#ifndef MOVINGPLATFORM_H
#define MOVINGPLATFORM_H

#include "Sprite.h"
#include "Box2D\Box2D.h"

class MovingPlatform
{
private:
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_bodyFixtureDef;
	Sprite m_sprite;
	b2PolygonShape m_shape;
	SDL_Texture* m_texture;
	SDL_Rect m_rect;
	SDL_Rect m_startRect;
public:
	MovingPlatform();
	MovingPlatform(SDL_Texture*, SDL_Rect, b2World*, SDL_Rect src, string type);

	void Update();
	void Draw();
	void Destroy();
	void Reset();
};

#endif