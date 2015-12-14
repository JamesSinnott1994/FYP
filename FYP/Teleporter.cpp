#include "stdafx.h"
#include "Teleporter.h"

bool Teleporter::instanceFlag = false;
Teleporter* Teleporter::instance = NULL;

Teleporter* Teleporter::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new Teleporter;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

Teleporter::Teleporter()
{

}

void Teleporter::Init(SDL_Rect pRect, b2World *pWorld, string speedType)
{
	// Position
	m_rect = pRect;

	// Box2D stuff
	m_bodyDef.type = b2_staticBody;
	m_bodyDef.position.Set(pRect.x, pRect.y);
	m_body = pWorld->CreateBody(&m_bodyDef);

	m_shape.SetAsBox(pRect.w, pRect.h);
	m_bodyFixtureDef.shape = &m_shape;

	m_body->CreateFixture(&m_bodyFixtureDef);

	// Teleporter sprite
	m_animationSprite = new Sprite();
	m_source = { 0, 0, 587, 368 };
	m_animationSprite->Init("Images/Teleporter.png", pRect, m_source);
	m_animationSprite->SetOffset(SDL_Point{ 293.5f, 184 });
	gSpriteClips[ANIMATION_FRAMES];
	m_animationFrames = 0;

	m_animationTime = 0;
	m_animationTimeLab = 1200;
	m_animationTimeLaptop = 0;
	m_limit = 0;
	if (speedType == "labSpeed")
	{
		m_limit = m_animationTimeLab;
	}
	else
	{
		m_limit = m_animationTimeLaptop;
	}

	m_switchedOn = false;

	SpriteClips();

	//cout << m_rect.x << endl;

	//cout << m_body->GetPosition().x << endl;
}

void Teleporter::SpriteClips()
{
	// Sprite clips
	/*gSpriteClips[2] = { 0, 0, 192, 368 };
	gSpriteClips[1] = { 198, 0, 192, 368 };
	gSpriteClips[0] = { 395, 0, 192, 368 };*/

	gSpriteClips[0] = { 0, 0, 192, 368 };
	gSpriteClips[1] = { 198, 0, 192, 368 };
	gSpriteClips[2] = { 395, 0, 192, 368 };
}

void Teleporter::Draw()
{
	SDL_Rect* currentRunnerClip = &gSpriteClips[m_animationFrames / ANIMATION_FRAMES];

	m_animationSprite->SetSourceRect(*currentRunnerClip);
	m_animationSprite->Draw(1);
}

void Teleporter::Update()
{
	//// Update sprite position
	//m_rect.x = m_body->GetPosition().x;
	//m_rect.y = m_body->GetPosition().y;
	//m_animationSprite->SetPosition(m_body->GetPosition().x, m_body->GetPosition().y);
	//m_animationSprite->SetPosition(m_body->GetPosition().x, m_body->GetPosition().y);

	//m_source = { 0, 0, 77, 107 };
	//m_animationSprite->Init("Images/Teleporter.png", m_rect, m_source);
	//m_animationSprite->SetOffset(SDL_Point{ 293.5f, 184 });

	// Cycle animation
	if (m_animationFrames / 3 >= ANIMATION_FRAMES)
	{
		m_animationFrames = 0;
	}

	// Go through frames
	m_animationTime++;
	if (m_animationTime > m_limit && m_switchedOn)
	{
		++m_animationFrames;
		m_animationTime = 0;
	}
}

bool Teleporter::CheckCollision(b2Body* playerBody)
{
	bool collided = (b2TestOverlap(m_body->GetFixtureList()->GetAABB(0), playerBody->GetFixtureList()->GetAABB(0)));
	if (collided)
	{
		//m_body->GetWorld()->DestroyBody(m_body);
		//cout << "collided" << endl;
	}

	return collided;
}

SDL_Rect Teleporter::GetRect()
{
	return m_rect;
}