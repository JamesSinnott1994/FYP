#include "stdafx.h"
#include "MovingPlatform.h"

MovingPlatform::MovingPlatform(){}

MovingPlatform::MovingPlatform(SDL_Texture* text, SDL_Rect pRect, b2World* wWorld, SDL_Rect src, string speedType)
{
	m_rect = pRect;
	m_startRect = pRect;

	// Define the ground body.
	m_bodyDef.position.Set(pRect.x, pRect.y);
	m_bodyDef.type = b2_staticBody;

	// Define the ground box shape.
	// The extents are the half-widths of the box.
	m_shape.SetAsBox(pRect.w / 2, pRect.h / 2);
	m_bodyFixtureDef.shape = &m_shape;

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	m_body = wWorld->CreateBody(&m_bodyDef);

	// Collision Filtering
	short GROUP_PLATFORM = 3;

	m_bodyFixtureDef.filter.groupIndex = GROUP_PLATFORM;

	// Add the ground fixture to the ground body.
	m_body->CreateFixture(&m_bodyFixtureDef);
	m_sprite.Init(text, pRect, src);
	m_sprite.SetOffset(SDL_Point{ 48, 16 });
}

void MovingPlatform::Update()
{

}

void MovingPlatform::Draw()
{
	m_sprite.Draw(1);
}

void MovingPlatform::Destroy()
{
	m_body->GetWorld()->DestroyBody(m_body);
}

void MovingPlatform::Reset()
{
	m_rect = m_startRect;
}