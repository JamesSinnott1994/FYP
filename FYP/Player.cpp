#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	
}

void Player::Init(SDL_Rect pRect, b2World *pWorld)
{
	// Position
	m_rect = pRect;

	// Box2D stuff
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(pRect.x, pRect.y);
	m_body = pWorld->CreateBody(&m_bodyDef);

	m_shape.SetAsBox(pRect.w / 2 - 20, (pRect.h / 2) - 2);
	m_bodyFixtureDef.shape = &m_shape;

	m_body->CreateFixture(&m_bodyFixtureDef);

	// Player Initial idle sprite
	m_playerIdleSprite = new Sprite();
	m_source = { 0, 0, 77, 107 };
	m_playerIdleSprite->Init("Images/PlayerIdleRight.png", pRect, m_source);
	m_playerIdleSprite->SetOffset(SDL_Point{ 38.5f, 53.5f });
	m_idle = true;
	m_drawn = true;

	// Initial direction
	m_movingLeft = false;
	m_movingRight = true;

	// Player running animation
	m_playerRunningSprite = new Sprite();
	m_source = { 0, 0, 912, 107 };
	m_playerRunningSprite->Init("Images/PlayerRunningRight.png", pRect, m_source);
	m_playerRunningSprite->SetOffset(SDL_Point{ 38.5f, 53.5f });
	m_runningFrames = 0;
	m_runningAnimationTime = 0;
	gSpriteRunningClipsRight[RUNNING_ANIMATION_FRAMES];
	gSpriteRunningClipsLeft[RUNNING_ANIMATION_FRAMES];
	m_running = false;

	// Jump
	m_canJump = false;

	// Score
	m_score = 0;

	// Health
	m_health = 100;

	SpriteClips();
}

void Player::SpriteClips()
{
	float scale = 2;

	// Running sprite clips
	gSpriteRunningClipsRight[0] = { 0, 3, 74, 103 };
	gSpriteRunningClipsRight[1] = { 91, 1, 68, 105 };
	gSpriteRunningClipsRight[2] = { 176, 0, 74, 106 };
	gSpriteRunningClipsRight[3] = { 266, 2, 82, 104 };
	gSpriteRunningClipsRight[4] = { 364, 4, 84, 102 };
	gSpriteRunningClipsRight[5] = { 466, 3, 72, 103 };
	gSpriteRunningClipsRight[6] = { 557, 1, 68, 105 };
	gSpriteRunningClipsRight[7] = { 639, 1, 73, 105 };
	gSpriteRunningClipsRight[8] = { 720, 2, 82, 104 };
	gSpriteRunningClipsRight[9] = { 827, 4, 83, 102 };

	gSpriteRunningClipsLeft[0] = { 837, 3, 74, 103 };
	gSpriteRunningClipsLeft[1] = { 752, 1, 68, 105 };
	gSpriteRunningClipsLeft[2] = { 662, 0, 73, 106 };
	gSpriteRunningClipsLeft[3] = { 563, 2, 82, 104 };
	gSpriteRunningClipsLeft[4] = { 463, 4, 84, 102 };
	gSpriteRunningClipsLeft[5] = { 373, 3, 72, 103 };
	gSpriteRunningClipsLeft[6] = { 286, 1, 68, 105 };
	gSpriteRunningClipsLeft[7] = { 199, 1, 73, 105 };
	gSpriteRunningClipsLeft[8] = { 109, 2, 82, 104 };
	gSpriteRunningClipsLeft[9] = { 1, 4, 83, 102 };
}

void Player::Draw()
{
	//Render current frame
	if (m_movingRight)
		currentRunnerClip = &gSpriteRunningClipsRight[m_runningFrames / 10];
	else if (m_movingLeft)
		currentRunnerClip = &gSpriteRunningClipsLeft[m_runningFrames / 10];

	if (m_idle)
	{
		m_playerIdleSprite->Draw(1);
	}
	else if (m_running)
	{
		m_playerRunningSprite->SetSourceRect(*currentRunnerClip);
		m_playerRunningSprite->Draw(1);
	}
}

void Player::Update()
{
	cout << m_score << endl;

	if (CheckScoreCollision())
	{
		m_score += 5;
	}
	else if (CheckHealthCollision())
	{
		m_health += 50;
	}

	// Can jump if y-velocity is 0
	if (m_body->GetLinearVelocity().y == 0)
	{
		m_canJump = true;
	}

	else
	{
		// Cannot jump
		m_canJump = false;
		m_bodyFixtureDef.friction = 0;
	}

	// Call move
	Move();

	// Draw player when idle
	if (m_idle)
	{
		if (m_movingLeft && !m_drawn)
		{
			m_source = { 0, 0, 77, 107 };
			m_playerIdleSprite->Init("Images/PlayerIdleLeft.png", m_rect, m_source);
			m_playerIdleSprite->SetOffset(SDL_Point{ 38.5f, 53.5f });
			m_drawn = true;
		}
		else if (m_movingRight && !m_drawn)
		{
			m_source = { 0, 0, 77, 107 };
			m_playerIdleSprite->Init("Images/PlayerIdleRight.png", m_rect, m_source);
			m_playerIdleSprite->SetOffset(SDL_Point{ 38.5f, 53.5f });
			m_drawn = true;
		}
	}

	// Update sprite position
	m_rect.x = m_body->GetPosition().x;
	m_rect.y = m_body->GetPosition().y;
	m_playerIdleSprite->SetPosition(m_body->GetPosition().x, m_body->GetPosition().y);
	m_playerRunningSprite->SetPosition(m_body->GetPosition().x, m_body->GetPosition().y);

	//Cycle animation
	if (m_runningFrames / 10 >= RUNNING_ANIMATION_FRAMES)
	{
		m_runningFrames = 0;
	}
}

bool Player::CheckScoreCollision()
{
	return PickupManager::GetInstance()->CheckScoreCollision(m_body);
}

bool Player::CheckHealthCollision()
{
	return PickupManager::GetInstance()->CheckHealthCollision(m_body);
}

void Player::Move()
{
	// Key presses
	// Move left
	if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_a) || KeyBoardInput::GetInstance()->isKeyPressed(SDLK_LEFT))
	{
		m_body->SetLinearVelocity(b2Vec2(-2, m_body->GetLinearVelocity().y));

		// Change sprite image if not already moving left
		if (!m_movingLeft)
		{
			m_source = { 0, 0, 912, 107 };
			m_playerRunningSprite->Init("Images/PlayerRunningLeft.png", m_rect, m_source);
			m_playerRunningSprite->SetOffset(SDL_Point{ 38.5f, 53.5f });
		}

		// Change booleans
		m_movingLeft = true;
		m_movingRight = false;
		m_running = true;
		m_idle = false;
		m_drawn = false;

		// Increase running frames
		m_runningAnimationTime++;
		if (m_runningAnimationTime >= 60)
		{
			++m_runningFrames;
			m_runningAnimationTime = 0;
		}
	}
	// Move right
	else if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_d) || KeyBoardInput::GetInstance()->isKeyPressed(SDLK_RIGHT))
	{
		m_body->SetLinearVelocity(b2Vec2(2, m_body->GetLinearVelocity().y));

		// Change sprite image if not already moving right
		if (!m_movingRight)
		{
			m_source = { 0, 3, 912, 107 };
			m_playerRunningSprite->Init("Images/PlayerRunningRight.png", m_rect, m_source);
			m_playerRunningSprite->SetOffset(SDL_Point{ 38.5f, 53.5f });
		}

		// Change booleans
		m_movingLeft = false;
		m_movingRight = true;
		m_running = true;
		m_idle = false;
		m_drawn = false;

		// Increase running frames
		m_runningAnimationTime++;
		if (m_runningAnimationTime >= 60)
		{
			++m_runningFrames;
			m_runningAnimationTime = 0;
		}
	}
	// Jump
	else if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_SPACE) && m_canJump)
	{
		Jump();
	}
	else
	{
		m_running = false;
		m_idle = true;
		m_body->SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y));
	}
}

void Player::Jump()
{
	float impulse = -1 * 6.0f;
	m_body->ApplyLinearImpulse(b2Vec2(0, impulse), m_body->GetWorldCenter(), true);
}

b2Body *Player::getBody()
{
	return m_body;
}

#pragma region Get/Set Score

int Player::GetScore()
{
	return m_score;
}
void Player::SetScore(int myScore)
{
	m_score = myScore;
}

#pragma endregion

