#include "stdafx.h"
#include "Robot.h"

Robot::Robot()
{

}

Robot::Robot(SDL_Rect pRect, b2World* wWorld, int direction, string speedType, int width, int height)
{
	world = wWorld;

	// Screen width and height
	m_width = width;
	m_height = height;

	// Position
	m_rect.x = pRect.x;
	m_rect.y = pRect.y;
	m_rect.w = 59;
	m_rect.h = 96;
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

	// Box2D stuff
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(m_rect.x, m_rect.y);
	m_body = wWorld->CreateBody(&m_bodyDef);

	// Define the ground box shape.
	// The extents are the half-widths of the box.
	m_shape.SetAsBox(m_rect.w / 2, m_rect.h / 2);
	m_bodyFixtureDef.shape = &m_shape;

	// Collision Filtering
	short GROUP_PLAYER = -1;
	short GROUP_ROBOT = -2;

	m_bodyFixtureDef.filter.groupIndex = GROUP_ROBOT;

	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&m_bodyFixtureDef);

	// Grunt Initial idle sprite
	m_idleSprite = new Sprite();
	m_source = { 0, 0, m_rect.w, m_rect.h };
	m_idleSprite->Init("Images/Enemy/RobotIdleLeft.png", m_rect, m_source);
	m_idleSprite->SetOffset(SDL_Point{ m_rect.w / 2, m_rect.h / 2 });

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
}

void Robot::Draw()
{
	if (m_alive)
	{
		// Draw
		if (m_idle)
		{
			m_idleSprite->Draw(1);
		}
	}
}

void Robot::Update(SDL_Rect &playerRect)
{
	ChangeDirection(playerRect.x);

	// Update sprite position
	m_rect.x = m_body->GetPosition().x;
	m_rect.y = m_body->GetPosition().y;
	m_idleSprite->SetPosition(m_body->GetPosition().x, m_body->GetPosition().y);
}

void Robot::Reset()
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

void Robot::ResetTimer()
{
	m_shootTimer = 0;
}

void Robot::Destroy()
{
	m_body->GetWorld()->DestroyBody(m_body);
}

void Robot::ChangeDirection(int &playerXPos)
{
	if (playerXPos < m_rect.x && m_facingRight)// Player is to the left of grunt
	{
		m_facingRight = false;
		m_source = { 0, 0, 59, 96 };
		m_idleSprite->Init("Images/Enemy/RobotIdleLeft.png", m_rect, m_source);
		m_idleSprite->SetOffset(SDL_Point{ m_rect.w / 2, m_rect.h / 2 });
	}
	else if (playerXPos > m_rect.x && !m_facingRight)// Player is to the right of grunt
	{
		m_facingRight = true;
		m_source = { 0, 0, 59, 96 };
		m_idleSprite->Init("Images/Enemy/RobotIdleRight.png", m_rect, m_source);
		m_idleSprite->SetOffset(SDL_Point{ m_rect.w / 2, m_rect.h / 2 });
	}
}

#pragma region Getters/Setters

bool Robot::GetAlive()
{
	return m_alive;
}

void Robot::SetAlive(bool myAlive)
{
	m_alive = myAlive;
}

#pragma endregion