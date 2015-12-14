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

void PlatformManager::Draw()
{
	for each(Platform* plat in m_platforms)
	{
		plat->Draw();
	}
}