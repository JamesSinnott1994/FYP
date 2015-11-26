#include "stdafx.h"
#include "PickupManager.h"

bool PickupManager::instanceFlag = false;
PickupManager* PickupManager::instance = NULL;

PickupManager* PickupManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new PickupManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void PickupManager::Draw()
{
	for each(Score* score in m_scores)
	{
		score->Draw();
	}

	for each(Health* health in m_healthPickups)
	{
		health->Draw();
	}
}

void PickupManager::Update()
{

}

void PickupManager::addScorePickups(SDL_Rect pRect, b2World* world)
{
	Score* temp = new Score(m_scoreTexture, pRect, world, m_scoreSource);

	m_scores.push_back(temp);
}

void PickupManager::addHealthPickups(SDL_Rect pRect, b2World* world)
{
	Health* temp = new Health(m_healthTexture, pRect, world, m_healthSource);

	m_healthPickups.push_back(temp);
}

bool PickupManager::CheckScoreCollision(b2Body*playerBody)
{
	for each(Score* score in m_scores)
	{
		if (score->GetAlive())
		{
			if (score->CheckCollision(playerBody))
			{
				return true;
			}
		}
	}
	return false;
}

bool PickupManager::CheckHealthCollision(b2Body*playerBody)
{
	for each(Health* health in m_healthPickups)
	{
		if (health->GetAlive())
		{
			if (health->CheckCollision(playerBody))
			{
				return true;
			}
		}
	}
	return false;
}