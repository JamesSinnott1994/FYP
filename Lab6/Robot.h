#ifndef ROBOT_H
#define ROBOT_H

#include "Sprite.h"

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
	const int RUNNING_ANIMATION_FRAMES = 8;
	SDL_Rect gSpriteRunningClipsRight[8];
	SDL_Rect gSpriteRunningClipsLeft[8];
	SDL_Rect* currentRunnerClip;
	int m_runningFrames;
	int m_runningAnimationTime;
	int m_runningAnimationLimit;
	int m_runningAnimationLimitLab;
	int m_runningAnimationLimitLaptop;

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

public:
	Robot();

	Robot(SDL_Rect pRect, b2World* wWorld, int direction, string speedType, int width, int height);

	void Draw();
	void Update(SDL_Rect &playerRect);
	void Reset();
	void ResetTimer();
	void Destroy();

	// Grunt states
	enum State { IDLE, RUNNING, SHOOTING, DEAD };
	State FiniteStateMachine();

	void ChangeDirection(int &playerXPos);

	bool GetAlive();
	void SetAlive(bool);
};

#endif