#include "stdafx.h"
#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

bool CollisionManager::PlayerScoreCollision(Player &player, std::vector<Score2> &scores2Vector)
{
	for (std::vector<Score2>::iterator it = scores2Vector.begin(); it != scores2Vector.end(); ++it)
	{
		if (player.getSprite()->getGlobalBounds().intersects(it->getSprite().getGlobalBounds()) && it->getAlive())
		{
			player.setScore(player.getScore() + 5);
			it->setAlive(false);
			return true;
		}
	}
	return false;
}

bool CollisionManager::PlayerPlatformCollision(Player &player)
{
	std::list<Platform> platforms = PlatformManager::GetInstance()->platformObjectList();

	for (std::list<Platform>::iterator it = platforms.begin(); it != platforms.end(); ++it)
	{
		if (player.getSprite()->getPosition().y <= it->getRectangle().getGlobalBounds().top
			&& player.getSprite()->getPosition().x >= it->getRectangle().getGlobalBounds().left
			&& player.getSprite()->getPosition().x <= (it->getRectangle().getGlobalBounds().left + it->getRectangle().getGlobalBounds().width))
		{
			player.setOnTopOfPlatform(true);
		}
		else
		{
			player.setOnTopOfPlatform(false);
		}


		if (player.getSprite()->getGlobalBounds().intersects(it->getRectangle().getGlobalBounds()))
		{
			player.setCollidingWithPlatform(true);
			return true;
		}
	}
	player.setCollidingWithPlatform(false);
	return false;
}