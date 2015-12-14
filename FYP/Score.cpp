#include "stdafx.h"
#include "Score.h"

Score::Score()
{
}

Score::Score(SDL_Texture* text, SDL_Rect pRect, b2World *wWorld, SDL_Rect src)
{
	myRect = pRect;

	// Define the ground body.
	myBodyDef.position.Set(pRect.x, pRect.y);
	myBodyDef.type = b2_staticBody;

	// Define the ground box shape.
	// The extents are the half-widths of the box.
	myShape.SetAsBox(pRect.w / 2, pRect.h / 2);

	myBodyFixtureDef.shape = &myShape;

	// The body is also added to the world.
	myBody = wWorld->CreateBody(&myBodyDef);

	// Add the ground fixture to the ground body.
	myBody->CreateFixture(&myBodyFixtureDef);
	sprite.Init(text, pRect, src);
	sprite.SetOffset(SDL_Point{ 16, 16 });

	m_alive = true;
}

void Score::Draw()
{
	if (m_alive)
		sprite.Draw(1);
}

void Score::Update()
{

}

void Score::Reset()
{
	m_alive = true;
	myBody->SetActive(true);
}

bool Score::CheckCollision(b2Body* playerBody)
{
	bool collided = (b2TestOverlap(myBody->GetFixtureList()->GetAABB(0), playerBody->GetFixtureList()->GetAABB(0)));
	if (collided)
	{
		m_alive = false;
		myBody->SetActive(false);
		SoundManager::GetInstance()->play(SoundManager::SCORE_PICKUP);
	}

	return collided;
}

bool Score::GetAlive()
{
	return m_alive;
}

void Score::SetAlive(bool myAlive)
{
	m_alive = myAlive;
}