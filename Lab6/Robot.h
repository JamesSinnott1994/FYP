#ifndef ROBOT_H
#define ROBOT_H

#include "Sprite.h"
#include "RobotBullet.h"
#include <list>

class Robot
{
private:
	// Box2D
	b2World* world;
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	b2FixtureDef m_bodyFixtureDef;
	b2PolygonShape m_shape;

	// Sprite
	Sprite* m_idleSprite;

	// SDL
	SDL_Texture* m_texture;
	SDL_Rect m_rect;
	SDL_Rect m_resetRect;// Used for reset
	SDL_Rect m_source;

	// Running animation
	Sprite* m_runningSprite;
	const int RUNNING_ANIMATION_FRAMES = 10;
	SDL_Rect gSpriteRunningClipsRight[10];
	SDL_Rect gSpriteRunningClipsLeft[10];
	SDL_Rect* currentRunnerClip;
	int m_runningFrames;
	int m_runningAnimationTime;
	int m_runningAnimationLimit;
	int m_runningAnimationLimitLab;
	int m_runningAnimationLimitLaptop;

	// Shooting animation

	// Boolean
	bool m_facingRight;
	bool m_movingRight;
	bool m_movingLeft;
	bool m_idle;
	bool m_running;
	bool m_shooting;
	bool m_inRange;
	bool m_dead;
	bool m_alive;
	bool m_playerToTheLeft;
	bool m_drawn;// For drawing idle image when changing direction
	bool m_canCreateBullet;

	// Screen width and height
	int m_width;
	int m_height;

	// Shooting
	int m_shootTimer;
	int m_shootTimerLaptop;
	int m_shootTimerLab;
	int m_shootTimerLimit;

	// Bullets
	list<RobotBullet*> m_bullets;
	list<RobotBullet*>::iterator m_bulletIterator;

public:
	Robot();

	Robot(SDL_Rect pRect, b2World* wWorld, int direction, string speedType, int width, int height);

	void SpriteClips();

	void Draw();
	void Update(SDL_Rect &playerRect, int noOfBullets, int maxBullets);
	void Reset();
	void ResetTimer();
	void Destroy();

	void Running();
	void Animation();
	void Shoot(int noOfBullets, int maxBullets);
	list<RobotBullet*> CreateBullet(list<RobotBullet*>m_robotBullets);

	// Grunt states
	enum State { IDLE, RUNNING, SHOOTING, DEAD };
	State FiniteStateMachine();

	bool InRange();
	void SetInRange(bool);
	bool InRangeOfPlayer(SDL_Rect &playerRect);

	bool CanCreateBullet();
	void SetCanCreateBullet(bool myCanCreateBullet);

	bool GetAlive();
	void SetAlive(bool);

	void ChangeDirection(int &playerXPos);
	bool PlayerToTheLeft();
	void SetPlayerToTheLeft(bool);

	bool RobotCheckCollision(b2Body* bulletBody);
	bool CheckBulletPlayerCollision(b2Body* playerBody);

	void Fell();
};

#endif