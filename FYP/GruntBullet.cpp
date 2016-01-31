#include "stdafx.h"
#include "GruntBullet.h"

GruntBullet::GruntBullet() {}

GruntBullet::GruntBullet(SDL_Texture* text, int width, int height, SDL_Rect pRect, b2World* wWorld, SDL_Rect src, bool facingRight)
{
	m_rect = pRect;

	m_width = width;
	m_height = height;

	// Define the ground body.
	myBodyDef.position.Set(m_rect.x, m_rect.y);
	myBodyDef.type = b2_kinematicBody;
	myBodyDef.bullet = true;

	// Define the ground box shape.
	// The extents are the half-widths of the box.
	myShape.SetAsBox(m_rect.w / 2, m_rect.h / 2);

	myBodyFixtureDef.shape = &myShape;

	// The body is also added to the world.
	myBody = wWorld->CreateBody(&myBodyDef);

	// Add the ground fixture to the ground body.
	myBody->CreateFixture(&myBodyFixtureDef);

	// Sprite
	sprite = new Sprite();
	sprite->Init(text, pRect, src);
	sprite->SetOffset(SDL_Point{ m_rect.w / 2, m_rect.h / 2 });

	// Direction
	m_facingRight = facingRight;
}

void GruntBullet::Draw()
{
	sprite->Draw(1);
}

void GruntBullet::Update()
{
	if (m_facingRight)
		myBody->SetLinearVelocity(b2Vec2(4, myBody->GetLinearVelocity().y));
	else
		myBody->SetLinearVelocity(b2Vec2(-4, myBody->GetLinearVelocity().y));

	sprite->SetPosition(myBody->GetPosition().x, myBody->GetPosition().y);
}

bool GruntBullet::OutOfBounds(SDL_Rect &gruntRect)
{
	float distance;

	distance = sqrt(((m_rect.x - gruntRect.x)*(m_rect.x - gruntRect.x)) + ((m_rect.y - gruntRect.y)*(m_rect.y - gruntRect.y)));

	if (distance > m_width || myBody->GetPosition().x < 0)
	{
		return true;
	}
	else
		return false;
}