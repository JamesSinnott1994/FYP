#include "stdafx.h"
#include "Grunt.h"

Grunt::Grunt() {}

Grunt::Grunt(SDL_Rect pRect, b2World* wWorld, int color, int direction, string speedType, int width, int height)
{
	world = wWorld;

	// Screen width and height
	m_width = width;
	m_height = height;

	// Position
	m_rect.x = pRect.x;
	m_rect.y = pRect.y;
	m_rect.w = 58;
	m_rect.h = 80;

	m_resetRect = m_rect;

	// Direction
	if (direction == 1)// RIGHT
	{
		m_facingRight = true;
		m_movingRight = true;
		m_movingLeft = false;
	}
	else // LEFT
	{
		m_facingRight = false;
		m_movingRight = false;
		m_movingLeft = true;
	}

	// Define the ground body.
	m_bodyDef.position.Set(m_rect.x, m_rect.y);
	m_bodyDef.type = b2_dynamicBody;

	// Define the ground box shape.
	// The extents are the half-widths of the box.
	m_shape.SetAsBox(m_rect.w / 2, m_rect.h / 2);
	m_bodyFixtureDef.shape = &m_shape;

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	m_body = wWorld->CreateBody(&m_bodyDef);

	// Collision Filtering
	short GROUP_PLAYER = -1;
	short GROUP_GRUNT = -2;

	m_bodyFixtureDef.filter.groupIndex = GROUP_GRUNT;

	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&m_bodyFixtureDef);

	// Load assets
	LoadAssets(color, direction);

	// Sprites
	SpriteClips();

	// Grunt states
	m_idle = true;
	m_running = false;
	m_shooting = false;
	m_inRange = false;
	m_dead = false;
	m_alive = true;
	m_playerToTheLeft = false;
	m_drawn = true;
	m_canCreateBullet = false;

	// Running Frames/Animation
	gSpriteRunningClipsRight[RUNNING_ANIMATION_FRAMES];
	gSpriteRunningClipsLeft[RUNNING_ANIMATION_FRAMES];
	m_runningFrames = 0;
	m_runningAnimationTime = 0;
	m_runningAnimationLimit = 0;
	m_runningAnimationLimitLab = 60;
	m_runningAnimationLimitLaptop = 6;

	// Shoot timer
	m_shootTimerLaptop = 200;
	m_shootTimerLab = 2000;

	// Speed
	if (speedType == "labSpeed")
	{
		m_runningAnimationLimit = m_runningAnimationLimitLab;
		m_shootTimerLimit = m_shootTimerLab;
		m_shootTimer = m_shootTimerLimit;
	}
	else
	{
		m_runningAnimationLimit = m_runningAnimationLimitLaptop;
		m_shootTimerLimit = m_shootTimerLaptop;
		m_shootTimer = m_shootTimerLimit;
	}
}

void Grunt::LoadAssets(int color, int direction)
{
	// Grunt Initial idle sprite
	m_idleSprite = new Sprite();
	m_source = { 0, 0, m_rect.w, m_rect.h };

	// Get color type
	if (color == 1)
		colorString = "Red";
	else if (color == 2)
		colorString = "Green";
	else if (color == 3)
		colorString = "Blue";
	else if (color == 4)
		colorString = "Yellow";

	// Get direction
	if (direction == 1)
		directionString = "Right";
	else
		directionString = "Left";

	// Get File of image
	file = "Images/Enemy/" + colorString + "GruntIdle" + directionString + ".png";

	// Set sprite image
	m_idleSprite->Init(file, m_rect, m_source);
	m_idleSprite->SetOffset(SDL_Point{ m_source.w / 2, m_source.h / 2 });

	// Set running sprite image
	file = "Images/Enemy/" + colorString + "Running" + directionString + ".png";

	m_runningSprite = new Sprite();
	m_source = { 0, 0, 774, 80 };
	m_runningSprite->Init(file, m_rect, m_source);
	m_runningSprite->SetOffset(SDL_Point{ m_rect.w / 2, m_rect.h / 2 });
}

void Grunt::SpriteClips()
{
	// Running sprite clips
	gSpriteRunningClipsRight[0] = { 0, 0, 59, 80 };
	gSpriteRunningClipsRight[1] = { 112, 0, 49, 80 };
	gSpriteRunningClipsRight[2] = { 207, 0, 54, 80 };
	gSpriteRunningClipsRight[3] = { 302, 0, 61, 80 };
	gSpriteRunningClipsRight[4] = { 408, 0, 58, 80 };
	gSpriteRunningClipsRight[5] = { 520, 0, 49, 80 };
	gSpriteRunningClipsRight[6] = { 616, 0, 55, 80 };
	gSpriteRunningClipsRight[7] = { 708, 0, 66, 80 };

	gSpriteRunningClipsLeft[0] = { 714, 0, 60, 80 };
	gSpriteRunningClipsLeft[1] = { 612, 0, 49, 80 };
	gSpriteRunningClipsLeft[2] = { 512, 0, 54, 80 };
	gSpriteRunningClipsLeft[3] = { 410, 0, 61, 80 };
	gSpriteRunningClipsLeft[4] = { 308, 0, 57, 80 };
	gSpriteRunningClipsLeft[5] = { 203, 0, 49, 80 };
	gSpriteRunningClipsLeft[6] = { 102, 0, 55, 80 };
	gSpriteRunningClipsLeft[7] = { 0, 0, 65, 80 };
}

void Grunt::Draw()
{
	if (m_alive)
	{
		//Render current frame
		if (m_movingRight)
			currentRunnerClip = &gSpriteRunningClipsRight[m_runningFrames / RUNNING_ANIMATION_FRAMES];
		else if (m_movingLeft)
			currentRunnerClip = &gSpriteRunningClipsLeft[m_runningFrames / RUNNING_ANIMATION_FRAMES];

		// Draw
		if (m_idle)
		{
			m_idleSprite->Draw(1);
		}
		if (m_running)
		{
			m_runningSprite->SetSourceRect(*currentRunnerClip);
			m_runningSprite->Draw(1);
		}
	}
}

void Grunt::Update(SDL_Rect &playerRect, int noOfBullets, int maxBullets)
{
	// Update time to shoot
	if (m_shootTimer <= m_shootTimerLimit && m_inRange)
		m_shootTimer++;

	State s = FiniteStateMachine();

	switch (s)
	{
	case IDLE:
		break;
	case RUNNING:
		Running();
		break;
	case SHOOTING:
		Shoot(noOfBullets, maxBullets);
		break;
	case DEAD:
		break;
	}

	ChangeDirection(playerRect.x);

	m_inRange = InRangeOfPlayer(playerRect);

	//Animation();

	//Fell();

	// Update sprite position
	m_rect.x = m_body->GetPosition().x;
	m_rect.y = m_body->GetPosition().y;
	m_idleSprite->SetPosition(m_body->GetPosition().x, m_body->GetPosition().y);
	m_runningSprite->SetPosition(m_body->GetPosition().x, m_body->GetPosition().y);
}

Grunt::State Grunt::FiniteStateMachine()
{
	State s;
	if (m_idle)
		s = IDLE;
	if (m_running)
		s = RUNNING;
	if (m_inRange)
		s = SHOOTING;
	if (m_dead)
		s = DEAD;

	return s;
}

void Grunt::Animation()
{
	//Cycle animation
	if (m_runningFrames / RUNNING_ANIMATION_FRAMES >= RUNNING_ANIMATION_FRAMES)
	{
		m_runningFrames = 0;
	}
}

void Grunt::Running()
{
	if (m_facingRight)// RIGHT
	{
		m_body->SetLinearVelocity(b2Vec2(2, m_body->GetLinearVelocity().y - 0.000001f));

		// Change sprite image if not already moving right
		if (!m_movingRight)
		{
			file = "Images/Enemy/" + colorString + "Running" + directionString + ".png";

			m_source = { 0, 0, 774, 80 };
			m_runningSprite->Init("Images/Enemy/BlueRunningRight.png", m_rect, m_source);
			m_runningSprite->SetOffset(SDL_Point{ m_rect.w / 2, m_rect.h / 2 });
		}

		// Change booleans
		m_movingLeft = false;
		m_movingRight = true;

		// Increase running frames
		m_runningAnimationTime++;
		if (m_runningAnimationTime >= m_runningAnimationLimit)
		{
			++m_runningFrames;
			m_runningAnimationTime = 0;
		}
	}
	else // LEFT
	{
		m_body->SetLinearVelocity(b2Vec2(-2, m_body->GetLinearVelocity().y - 0.000001f));

		// Change sprite image if not already moving left
		if (!m_movingLeft)
		{
			file = "Images/Enemy/" + colorString + "Running" + directionString + ".png";

			m_source = { 0, 0, 774, 80 };
			m_runningSprite->Init("Images/Enemy/BlueRunningRight.png", m_rect, m_source);
			m_runningSprite->SetOffset(SDL_Point{ m_rect.w / 2, m_rect.h / 2 });
		}

		// Change booleans
		m_movingLeft = true;
		m_movingRight = false;

		// Increase running frames
		m_runningAnimationTime++;
		if (m_runningAnimationTime >= m_runningAnimationLimit)
		{
			++m_runningFrames;
			m_runningAnimationTime = 0;
		}

	}
}

void Grunt::Shoot(int noOfBullets, int maxBullets)
{
	if (m_shootTimer >= m_shootTimerLimit && noOfBullets < maxBullets)
	{
		//CreateBullet(m_gruntBullets);
		m_canCreateBullet = true;
		m_shootTimer = 0;
	}
	else
	{
		m_canCreateBullet = false;
	}
}

list<GruntBullet*> Grunt::CreateBullet(list<GruntBullet*>m_gruntBullets)
{
	SDL_Texture* m_bulletTexture = Sprite::loadTexture("Images/Enemy/GruntBullet.png", Renderer::GetInstance()->Get_SDL_RENDERER());
	SDL_Rect m_bulletSource = { 0, 0, 9, 6 };
	SDL_Rect m_bulletPos;

	if (m_facingRight)
		m_bulletPos = { m_rect.x + 34, m_rect.y - 3, 9, 6 };
	else
		m_bulletPos = { m_rect.x - 32, m_rect.y - 3, 9, 6 };

	GruntBullet* bullet = new GruntBullet(m_bulletTexture, m_width, m_height, m_bulletPos, world, m_bulletSource, m_facingRight, m_rect);

	m_gruntBullets.push_back(bullet);

	return m_gruntBullets;
}

void Grunt::Reset()
{
	m_body->SetTransform(b2Vec2(m_resetRect.x, m_resetRect.y), 0);
	m_alive = true;
	m_body->SetActive(true);
	m_idle = true;
	m_running = false;
	m_shooting = false;
	m_inRange = false;
	m_dead = false;
	m_playerToTheLeft = false;
	m_drawn = true;
	m_canCreateBullet = false;
	m_shootTimer = 0;
	m_body->SetLinearVelocity(b2Vec2(0, m_body->GetLinearVelocity().y - 0.000001f));
}

bool Grunt::GruntCheckCollision(b2Body* bulletBody)
{
	bool collided = (b2TestOverlap(m_body->GetFixtureList()->GetAABB(0), bulletBody->GetFixtureList()->GetAABB(0)));
	if (collided)
	{
		m_alive = false;
		m_body->SetActive(false);
	}

	return collided;
}

void Grunt::Destroy()
{
	m_body->GetWorld()->DestroyBody(m_body);
}

void Grunt::ChangeDirection(int &playerXPos)
{
	if (playerXPos < m_rect.x && m_facingRight)// Player is to the left of grunt
	{
		directionString = "Left";
		file = "Images/Enemy/" + colorString + "GruntIdle" + directionString + ".png";

		m_facingRight = false;
		m_source = { 0, 0, 58, 80 };
		m_idleSprite->Init(file, m_rect, m_source);
		m_idleSprite->SetOffset(SDL_Point{ m_rect.w / 2, m_rect.h / 2 });
	}
	else if (playerXPos > m_rect.x && !m_facingRight)// Player is to the right of grunt
	{
		directionString = "Right";
		file = "Images/Enemy/" + colorString + "GruntIdle" + directionString + ".png";

		m_facingRight = true;
		m_source = { 0, 0, 58, 80 };
		m_idleSprite->Init(file, m_rect, m_source);
		m_idleSprite->SetOffset(SDL_Point{ m_rect.w / 2, m_rect.h / 2 });
	}
}

bool Grunt::InRangeOfPlayer(SDL_Rect &playerRect)
{
	float distance;

	SDL_Point gruntCentre;
	gruntCentre.x = m_rect.x + (m_rect.w / 2);
	gruntCentre.y = m_rect.y + (m_rect.h / 2);

	SDL_Point playerCentre;
	playerCentre.x = playerRect.x + (playerRect.w / 2);
	playerCentre.y = playerRect.y + (playerRect.h / 2);

	// Get distance
	float distanceX;
	float distanceY;

	distanceX = gruntCentre.x - playerCentre.x;
	distanceY = gruntCentre.y - playerCentre.y;

	if (distanceX < 0)
		distanceX *= -1;

	if (distanceY < 0)
		distanceY *= -1;

	//cout << distanceY << endl;

	// Check if in range
	if (distanceX <= (m_width * 0.75f) && distanceY <= (playerRect.h / 2))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Grunt::CheckBulletPlayerCollision(b2Body* playerBody)
{
	if (m_bullets.size() > 0)
	{
		// Iterate through list of bullets
		for (m_bulletIterator = m_bullets.begin(); m_bulletIterator != m_bullets.end(); ++m_bulletIterator)
		{
			bool collided = (*m_bulletIterator)->CheckBulletPlayerCollision(playerBody);

			if (collided)
			{
				m_bullets.erase(m_bulletIterator);
			}

			return collided;
		}
	}
	else
	{
		return false;
	}
}

void Grunt::Fell()
{
	// Out of bounds from falling
	if (m_body->GetPosition().y >= m_height)
	{
		m_alive = false;
		cout << "Enemy killed" << endl;
	}
}

#pragma region Getters/Setters

bool Grunt::GetAlive()
{
	return m_alive;
}

void Grunt::SetAlive(bool myAlive)
{
	m_alive = myAlive;
}

bool Grunt::InRange()
{
	return m_inRange;
}

void Grunt::SetInRange(bool myInRange)
{
	m_inRange = myInRange;
}

bool Grunt::PlayerToTheLeft()
{
	return m_playerToTheLeft;
}

void Grunt::SetPlayerToTheLeft(bool myPlayerToTheLeft)
{
	m_playerToTheLeft = myPlayerToTheLeft;
}

bool Grunt::CanCreateBullet()
{
	return m_canCreateBullet;
}

void Grunt::SetCanCreateBullet(bool myCanCreateBullet)
{
	m_canCreateBullet = myCanCreateBullet;
}

#pragma endregion
