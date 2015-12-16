#ifndef TELEPORTER_H
#define TELEPORTER_H

#include "Sprite.h"

class Teleporter
{
public:
	static Teleporter* GetInstance();
	~Teleporter()
	{
		instanceFlag = false;
	}

	Teleporter();

	void Init(SDL_Rect pRect, b2World *pWorld);
	void Draw();
	void Update();
	void Destroy();
	void SetPosition(SDL_Rect position);

	void SpriteClips();

	bool CheckCollision(b2Body* playerBody);

	SDL_Rect GetRect();
private:
	static bool instanceFlag;
	static Teleporter* instance;

	// Box2D stuff
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2FixtureDef m_bodyFixtureDef;

	// Teleporter animation
	Sprite* m_animationSprite;
	const int ANIMATION_FRAMES = 3;
	SDL_Rect gSpriteClips[3];
	int m_animationFrames;

	SDL_Rect m_rect;
	SDL_Rect m_source;

	SDL_Texture* m_texture;

	int m_animationTime;
	int m_limit;
	int m_animationTimeLaptop;
	int m_animationTimeLab;

	bool m_switchedOn;
};

#endif