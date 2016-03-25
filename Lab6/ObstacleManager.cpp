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
	for each(ElectricBarrier* barrier in m_barriers)
	{
		barrier->Draw();
	}
}

void ObstacleManager::Update()
{
	for each(Mine* mine in m_mines)
	{
		mine->Update();
	}
	for each(ElectricBarrier* barrier in m_barriers)
	{
		barrier->Update();
	}
}

void ObstacleManager::Reset()
{
	for each(Mine* mine in m_mines)
	{
		mine->Reset();
	}
	for each(ElectricBarrier* barrier in m_barriers)
	{
		barrier->Reset();
	}
}

void ObstacleManager::Destroy()
{
	for each(Mine* mine in m_mines)
	{
		mine->Destroy();
	}
	for each(ElectricBarrier* barrier in m_barriers)
	{
		barrier->Destroy();
	}

	// Iterate through list of mines
	if (m_mines.size() > 0)
	{
		m_mines.clear();
	}
	if (m_barriers.size() > 0)
	{
		m_barriers.clear();
	}
}

void ObstacleManager::addMineObstacles(SDL_Rect pRect, b2World* world)
{
	Mine* temp = new Mine(m_mineTexture, pRect, world, m_mineSource);

	m_mines.push_back(temp);
}

void ObstacleManager::addElectricBarriers(SDL_Rect pRect, b2World* world, string speedType)
{
	ElectricBarrier* barrier = new ElectricBarrier(m_barrierTexture, pRect, world, m_barrierSource, speedType);

	m_barriers.push_back(barrier);
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
				return true;
			}
		}
	}
	return false;
}

bool ObstacleManager::CheckBarrierCollision(b2Body*playerBody)
{
	// Iterate through list of bullets
	for (m_barrierIterator = m_barriers.begin(); m_barrierIterator != m_barriers.end(); ++m_barrierIterator)
	{
		if ((*m_barrierIterator)->GetOn())
		{
			if ((*m_barrierIterator)->CheckCollision(playerBody))
			{
				return true;
			}
		}
	}
	return false;
}