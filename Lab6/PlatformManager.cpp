#include "stdafx.h"
#include "PlatformManager.h"

bool PlatformManager::instanceFlag = false;
PlatformManager* PlatformManager::instance = NULL;

PlatformManager* PlatformManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new PlatformManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void PlatformManager::addPlatform(SDL_Rect pRect, b2World* world, string type)
{
	if (type == "topPlatform")
	{
		m_platformTexture = Sprite::loadTexture("Images/platform.png", Renderer::GetInstance()->Get_SDL_RENDERER());
		m_platformSource = { 0, 0, 106, 29 };
	}
	else
	{
		m_platformTexture = Sprite::loadTexture("Images/bottomPlatform.png", Renderer::GetInstance()->Get_SDL_RENDERER());
		m_platformSource = { 0, 0, 106, 29 };
	}

	Platform* temp = new Platform(m_platformTexture, pRect, world, m_platformSource);

	m_platforms.push_back(temp);
}

void PlatformManager::addMovingPlatform(SDL_Rect pRect, b2World* world, string type)
{
	m_movingPlatformTexture = Sprite::loadTexture("Images/platform.png", Renderer::GetInstance()->Get_SDL_RENDERER());
	m_movingPlatformSource = { 0, 0, 106, 29 };

	MovingPlatform* temp = new MovingPlatform(m_movingPlatformTexture, pRect, world, m_movingPlatformSource, type);

	m_movingPlatforms.push_back(temp);
}

void PlatformManager::addMovePlatSensor(SDL_Rect pRect, b2World  *world, int src)
{
	MovingPlatform* temp = new MovingPlatform(pRect, world, src);

	movingPlatformsSensors.push_back(temp);
}

void PlatformManager::Draw()
{
	for each(Platform* plat in m_platforms)
	{
		plat->Draw();
	}
	for each(MovingPlatform* mPlat in m_movingPlatforms)
	{
		mPlat->Draw();
	}
}

void PlatformManager::Update()
{
	for each(MovingPlatform* mPlat in m_movingPlatforms)
	{
		mPlat->Update();
	}
}

bool PlatformManager::CheckCollision(b2Body*playerBody)
{
	for each (MovingPlatform* mPlat in m_movingPlatforms)
	{
		if (mPlat->CheckCollision(playerBody) && mPlat->GetType() == "platform")
		{
			xSpeedOfMovingPlatform = mPlat->GetBody()->GetLinearVelocity().x;
			return true;
		}
	}
	return false;
}

void PlatformManager::Destroy()
{
	for each(Platform* plat in m_platforms)
	{
		plat->Destroy();
	}
	for each(MovingPlatform* mPlat in m_movingPlatforms)
	{
		mPlat->Destroy();
	}
	for each(MovingPlatform* mPlat in movingPlatformsSensors)
	{
		mPlat->Destroy();
	}

	if (m_platforms.size() > 0)
	{
		m_platforms.clear();
	}
	if (m_movingPlatforms.size() > 0)
	{
		m_movingPlatforms.clear();
	}
	if (movingPlatformsSensors.size() > 0)
	{
		movingPlatformsSensors.clear();
	}
}