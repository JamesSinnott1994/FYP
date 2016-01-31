#include "stdafx.h"
#include <EnemyManager.h>


bool EnemyManager::instanceFlag = false;
EnemyManager* EnemyManager::instance = NULL;

EnemyManager* EnemyManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new EnemyManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void EnemyManager::Draw()
{
	for each(Grunt * grunt in m_grunts)
	{
		grunt->Draw();
	}
}
void EnemyManager::Update(SDL_Rect &playerRect)
{
	for each(Grunt * grunt in m_grunts)
	{
		grunt->Update(playerRect);
	}
}

void EnemyManager::addGrunt(SDL_Rect pRect, b2World* world, int color, int direction, string speedType, int width, int height)
{
	Grunt* grunt = new Grunt(pRect, world, color, direction, speedType, width, height);
	m_grunts.push_back(grunt);
}

void EnemyManager::Reset()
{
	for each(Grunt * grunt in m_grunts)
	{
		grunt->Reset();
	}
}

void EnemyManager::Destroy()
{
	for each(Grunt * grunt in m_grunts)
	{
		grunt->Destroy();
	}
	
	if (m_grunts.size() > 0)
	{
		m_grunts.clear();
	}

}