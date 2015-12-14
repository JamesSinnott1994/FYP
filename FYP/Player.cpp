#include "stdafx.h"
#include "Player.h"

Player::Player()
{
	
}

void Player::Init(SDL_Rect pRect, b2World *pWorld, string speedType)
{
	world = pWorld;

	// Position
	m_rect = pRect;
	m_startRect = pRect;

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
	m_alive = true;

	// Bullets
	m_timeToShoot = 500;
	m_shootTimerLab = 600;
	m_shootTimerLaptop = 120;

	m_runningAnimationLimit = 10;

	SpriteClips();

	// Timer
	timer = new Timer();
	timer->start();
}

void Player::SpriteClips()
{
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
	if (m_alive)
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

	// Draw bullets
	if (m_bullets.size() > 0)
	{
		for each(Bullet* bullet in m_bullets)
		{
			bullet->Draw();
		}
	}
}

void Player::Update()
{
	CheckCollisions();

	if (m_health <= 0)
	{
		m_alive = false;
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

	// Out of bounds from falling
	if (m_body->GetPosition().y >= 800)
	{
		m_health = 0;
	}

	// Call move
	if (m_alive)
	{
		Move();
	}

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

	// Update bullets
	if (m_bullets.size() > 0)
	{
		// Iterate through list of bullets
		for (m_bulletIterator = m_bullets.begin(); m_bulletIterator != m_bullets.end(); ++m_bulletIterator)
		{
			(*m_bulletIterator)->Update();

			// Remove bullet if out of bounds
			if ((*m_bulletIterator)->OutOfBounds(m_rect))
			{
				m_bullets.erase(m_bulletIterator);
				break;
			}
		}
	}
}

void Player::CheckCollisions()
{
	// Collision with health object
	if (CheckHealthCollision())
	{
		m_health += 50;
		if (m_health > 100)
		{
			SetHealth(100);
		}
	}

	// Collision with mine object
	if (CheckMineCollision())
	{
		// Kill player
		m_health -= 50;
	}

	if (CheckTeleporterCollision())
	{
		int t = 0;
	}

	//cout << (m_rect.x + m_rect.w) << endl;
}

bool Player::CheckScoreCollision()
{
	return PickupManager::GetInstance()->CheckScoreCollision(m_body);
}

bool Player::CheckHealthCollision()
{
	return PickupManager::GetInstance()->CheckHealthCollision(m_body);
}

bool Player::CheckMineCollision()
{
	return ObstacleManager::GetInstance()->CheckMineCollision(m_body);
}

bool Player::CheckTeleporterCollision()
{
	//SDL_Rect teleporterRect = Teleporter::GetInstance()->GetRect();

	//if (m_rect.x + m_rect.w >= teleporterRect.x)
	//	//&& m_rect.x <= teleporterRect.x + teleporterRect.w
	//	//&& m_rect.y + m_rect.h >= teleporterRect.y
	//	//&& m_rect.y <= teleporterRect.y + teleporterRect.h)
	//{
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}


	return Teleporter::GetInstance()->CheckCollision(m_body);
}

void Player::Move()
{
	// Key presses
	// Move left
	if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_a) || KeyBoardInput::GetInstance()->isKeyPressed(SDLK_LEFT))
	{
		m_body->SetLinearVelocity(b2Vec2(-2, m_body->GetLinearVelocity().y-0.000001f));

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
		//m_runningAnimationTime++;
		if (timer->getTicks() >= m_runningAnimationLimit)
		{
			timer->resetTicks();
			++m_runningFrames;
			m_runningAnimationTime = 0;
		}
	}
	// Move right
	else if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_d) || KeyBoardInput::GetInstance()->isKeyPressed(SDLK_RIGHT))
	{
		m_body->SetLinearVelocity(b2Vec2(2, m_body->GetLinearVelocity().y - 0.000001f));

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
		//m_runningAnimationTime++;
		if (timer->getTicks() >= m_runningAnimationLimit)
		{
			timer->resetTicks();
			++m_runningFrames;
			m_runningAnimationTime = 0;
		}
	}
	// Jump
	else if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_SPACE) && m_canJump)
	{
		Jump();
	}
	else if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_j))
	{
		if (timer->getTicks() >= m_timeToShoot)
		{
			timer->resetTicks();
			Shoot();
			SoundManager::GetInstance()->play(SoundManager::GUNSHOT);
		}
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

void Player::Shoot()
{
	SDL_Texture* m_bulletTexture = Sprite::loadTexture("Images/Bullet.png", Renderer::GetInstance()->Get_SDL_RENDERER());
	SDL_Rect m_bulletSource = { 0, 0, 63, 64 };
	SDL_Rect m_bulletPos;

	if (m_movingRight)
		m_bulletPos = { m_rect.x + m_rect.w - 22, m_rect.y - 24, 10, 10 };
	else
		m_bulletPos = { m_rect.x - 32, m_rect.y - 24, 10, 10 };

	Bullet* bullet = new Bullet(m_bulletTexture, m_bulletPos, world, m_bulletSource, m_movingRight);

	m_bullets.push_back(bullet);
}

b2Body *Player::getBody()
{
	return m_body;
}

void Player::Reset()
{
	// Reset variables
	m_body->SetTransform(b2Vec2(m_startRect.x, m_startRect.y), 0);
	m_alive = true;
	m_health = 100;
	m_score = 0;
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

#pragma region Get/Set Health

int Player::GetHealth()
{
	return m_health;
}
void Player::SetHealth(int myHealth)
{
	m_health = myHealth;
}

#pragma endregion

#pragma region Get/Set Alive

bool Player::GetAlive()
{
	return m_alive;
}
void Player::SetAlive(bool myAlive)
{
	m_alive = myAlive;
}

#pragma endregion


