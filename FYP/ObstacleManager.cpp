#include "stdafx.h"
#include "ObstacleManager.h"

bool ObstacleManager::instanceFlag = false;
ObstacleManager* ObstacleManager::instance = NULL;

ObstacleManager* ObstacleManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new ObstacleManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void ObstacleManager::Draw()
{
	for each(Mine* mine in m_mines)
	{
		mine->Draw();
	}
}

void ObstacleManager::Update()
{
	for each(Mine* mine in m_mines)
	{
		mine->Update();
	}
}

void ObstacleManager::addMineObstacles(SDL_Rect pRect, b2World* world)
{
	Mine* temp = new Mine(m_mineTexture, pRect, world, m_mineSource);

	m_mines.push_back(temp);
}

bool ObstacleManager::CheckMineCollision(b2Body*playerBody)
{
	// Iterate through list of bullets
	for (m_mineIterator = m_mines.begin(); m_mineIterator != m_mines.end(); ++m_mineIterator)
	{
		if ((*m_mineIterator)->GetAlive())
		{
			if ((*m_mineIterator)->CheckCollision(playerBody))
			{
				m_mines.erase(m_mineIterator);
				return true;
			}
		}
	}
	return false;
}