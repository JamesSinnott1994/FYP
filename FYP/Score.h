#ifndef SCORE_H
#define SCORE_H

#include <iostream> 
#include "sdl.h"
#include "Box2D\Box2D.h"
#include "Sprite.h"
#include "Renderer.h"

class Score
{
public:
	Score();
	Score(SDL_Texture*, SDL_Rect, b2World*, SDL_Rect src);
	// Public member functions
	void Draw();
	void Update();// bool hit);

	bool CheckCollision(b2Body* playerBody);

	bool GetAlive();
	void SetAlive(bool);

private:
	b2Body* myBody;
	b2BodyDef myBodyDef;
	b2FixtureDef myBodyFixtureDef;
	Sprite sprite;
	b2PolygonShape myShape;
	SDL_Texture* myTexture;

	SDL_Rect gSpriteClips;
	SDL_Rect myRect;

	bool m_alive;
};

#endif