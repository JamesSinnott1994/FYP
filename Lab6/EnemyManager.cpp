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

	for each(GruntBullet * gruntBullet in m_gruntBullets)
	{
		gruntBullet->Draw();
	}
}

bool EnemyManager::Update(SDL_Rect &playerRect, b2Body* playerBody)
{
	// Update grunts
	if (m_grunts.size() > 0)
	{
		for (m_gruntIterator = m_grunts.begin(); m_gruntIterator != m_grunts.end(); m_gruntIterator++)
		{
			if ((*m_gruntIterator)->GetAlive())
			{
				(*m_gruntIterator)->Update(playerRect, m_gruntBullets.size(), m_grunts.size() * 1);

				if ((*m_gruntIterator)->CanCreateBullet())
				{
					m_gruntBullets = (*m_gruntIterator)->CreateBullet(m_gruntBullets);
				}
			}
		}
	}

	// Update grunt bullets
	if (m_gruntBullets.size() > 0)
	{
		for (m_gruntBulletIterator = m_gruntBullets.begin(); m_gruntBulletIterator != m_gruntBullets.end(); m_gruntBulletIterator++)
		{
			if (!(*m_gruntBulletIterator)->Collided())
			{
				if ((*m_gruntBulletIterator)->Update(playerBody))
				{
					(*m_gruntBulletIterator)->SetAlive(false);
					return true;
				}
			}

			// Remove bullet if out of bounds
			if (!(*m_gruntBulletIterator)->GetAlive())
			{
				m_gruntBullets.erase(m_gruntBulletIterator);
				break;
			}

			// Remove bullet if out of bounds
			if ((*m_gruntBulletIterator)->OutOfBounds(playerRect))
			{
				m_gruntBullets.erase(m_gruntBulletIterator);
				break;
			}
		}
	}

	// Clear grunt bullets if too many
	if (m_gruntBullets.size() > m_grunts.size() * 2)
	{
		cout << "Too many bullets!!!" << endl;
		while (m_gruntBullets.size() > m_grunts.size() * 2)
		{
			DestroyBullets();
			ResetGruntTimers();
		}
	}

	return false;
}

bool EnemyManager::CheckBulletCollision(b2Body*bulletBody)
{
	// Iterate through list of bullets
	for (m_gruntIterator = m_grunts.begin(); m_gruntIterator != m_grunts.end(); ++m_gruntIterator)
	{
		if ((*m_gruntIterator)->GetAlive())
		{
			if ((*m_gruntIterator)->GruntCheckCollision(bulletBody))
			{
				//m_grunts.erase(m_gruntIterator);
				return true;
			}
		}
	}
	return false;
}

bool EnemyManager::GruntCheckCollision(b2Body* playerBody)
{
	if (m_gruntBullets.size() > 0)
	{
		for each(GruntBullet * gruntBullet in m_gruntBullets)
		{
			bool collided = gruntBullet->CheckBulletPlayerCollision(playerBody);
			if (collided)
				int t = 0;
			return collided;
		}
	}
	else
	{
		return false;
	}
}

void EnemyManager::DestroyBullets()
{
	for each(GruntBullet * grunt in m_gruntBullets)
	{
		grunt->Destroy();
	}

	if (m_gruntBullets.size() > 0)
	{
		m_gruntBullets.clear();
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

void EnemyManager::ResetGruntTimers()
{
	for each(Grunt * grunt in m_grunts)
	{
		grunt->ResetTimer();
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