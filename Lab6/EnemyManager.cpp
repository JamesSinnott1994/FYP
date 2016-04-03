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
	for each(Robot * robot in m_robots)
	{
		robot->Draw();
	}
	for each(GruntBullet * gruntBullet in m_gruntBullets)
	{
		gruntBullet->Draw();
	}
	for each(RobotBullet * robotBullet in m_robotBullets)
	{
		robotBullet->Draw();
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

	// Update robots
	if (m_robots.size() > 0)
	{
		for (m_robotIterator = m_robots.begin(); m_robotIterator != m_robots.end(); m_robotIterator++)
		{
			if ((*m_robotIterator)->GetAlive())
			{
				(*m_robotIterator)->Update(playerRect, m_robotBullets.size(), m_robots.size() * 1);
			}

			if ((*m_robotIterator)->CanCreateBullet())
			{
				m_robotBullets = (*m_robotIterator)->CreateBullet(m_robotBullets);
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

bool EnemyManager::UpdateRobotBullets(SDL_Rect &playerRect, b2Body* playerBody)
{
	// Update robot bullets
	if (m_robotBullets.size() > 0)
	{
		for (m_robotBulletIterator = m_robotBullets.begin(); m_robotBulletIterator != m_robotBullets.end(); m_robotBulletIterator++)
		{
			if (!(*m_robotBulletIterator)->Collided())
			{
				if ((*m_robotBulletIterator)->Update(playerBody))
				{
					(*m_robotBulletIterator)->SetAlive(false);
					return true;
				}
			}

			// Remove bullet if out of bounds
			if (!(*m_robotBulletIterator)->GetAlive())
			{
				m_robotBullets.erase(m_robotBulletIterator);
				break;
			}

			// Remove bullet if out of bounds
			if ((*m_robotBulletIterator)->OutOfBounds(playerRect))
			{
				m_robotBullets.erase(m_robotBulletIterator);
				break;
			}
		}
	}

	// Clear robot bullets if too many
	if (m_robotBullets.size() > m_robots.size() * 2)
	{
		cout << "Too many bullets!!!" << endl;
		while (m_robotBullets.size() > m_robots.size() * 2)
		{
			DestroyBullets();
			ResetGruntTimers();
		}
	}

	return false;
}

bool EnemyManager::CheckBulletGruntCollision(b2Body*bulletBody)
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

bool EnemyManager::CheckBulletRobotCollision(b2Body*bulletBody)
{
	// Iterate through list of bullets
	for (m_robotIterator = m_robots.begin(); m_robotIterator != m_robots.end(); ++m_robotIterator)
	{
		if ((*m_robotIterator)->GetAlive())
		{
			if ((*m_robotIterator)->RobotCheckCollision(bulletBody))
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
	for each(RobotBullet * robotBullet in m_robotBullets)
	{
		robotBullet->Destroy();
	}

	if (m_gruntBullets.size() > 0)
	{
		m_gruntBullets.clear();
	}
	if (m_robotBullets.size() > 0)
	{
		m_robotBullets.clear();
	}
}

void EnemyManager::addGrunt(SDL_Rect pRect, b2World* world, int color, int direction, string speedType, int width, int height)
{
	Grunt* grunt = new Grunt(pRect, world, color, direction, speedType, width, height);
	m_grunts.push_back(grunt);
}

void EnemyManager::addRobot(SDL_Rect pRect, b2World* world, int direction, string speedType, int width, int height)
{
	Robot* robot = new Robot(pRect, world, direction, speedType, width, height);
	m_robots.push_back(robot);
}

void EnemyManager::Reset()
{
	for each(Grunt * grunt in m_grunts)
	{
		grunt->Reset();
	}
	for each(Robot * robot in m_robots)
	{
		robot->Reset();
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
	for each(Robot * robot in m_robots)
	{
		robot->Destroy();
	}
	
	if (m_grunts.size() > 0)
	{
		m_grunts.clear();
	}
	if (m_robots.size() > 0)
	{
		m_robots.clear();
	}

	DestroyBullets();

}