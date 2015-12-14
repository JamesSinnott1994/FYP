#ifndef PLAYER_H
#define PLAYER_H

#include "sdl.h"
#include "Box2D\Box2D.h"
#include "Sprite.h"
#include "KeyBoardInput.h"
#include "PickupManager.h"
#include "ObstacleManager.h"
#include "Bullet.h"
#include "Teleporter.h"

class Player{
public:
	Player();

	void Init(SDL_Rect, b2World*, string speedType);
	void Draw();
	void Update();
	void Move();
	void Jump();
	void Shoot();

	void CheckCollisions();

	void SpriteClips();

	b2Body* getBody();

	bool m_movingLeft;
	bool m_movingRight;

	// Score
	int GetScore();
	void SetScore(int);

	// Health
	int GetHealth();
	void SetHealth(int);

	bool CheckScoreCollision();
	bool CheckHealthCollision();
	bool CheckMineCollision();
	bool CheckTeleporterCollision();
private:
	SDL_Rect m_rect;
	SDL_Rect m_source;

	// Box2D stuff
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2PolygonShape m_shape;
	b2FixtureDef m_bodyFixtureDef;

	// Idle sprite
	Sprite* m_playerIdleSprite;
	bool m_idle;
	bool m_drawn;

	// Running animation
	Sprite* m_playerRunningSprite;
	const int RUNNING_ANIMATION_FRAMES = 10;
	SDL_Rect gSpriteRunningClipsRight[10];
	SDL_Rect gSpriteRunningClipsLeft[10];
	SDL_Rect* currentRunnerClip;
	int m_runningFrames;
	int m_runningAnimationTime;
	int m_runningAnimationLimit;
	bool m_running;

	// Jump
	bool m_canJump;

	// Score
	int m_score;

	// Health
	int m_health;

	// Bullets
	list<Bullet*> m_bullets;
	int m_timeToShoot;
	int m_shootTimerLaptop;
	int m_shootTimerLab;
	int m_shootTimerLimit;
	std::list<Bullet*>::iterator m_bulletIterator;

	// Box2D
	b2World* world;
};

#endif