#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include "Player.h"
#include "PickupManager.h"
#include "Score2.h"
#include "Platform.h"
#include "PlatformManager.h"

class CollisionManager
{
public:
	CollisionManager();

	bool PlayerScoreCollision(Player &player, std::vector<Score2> &scoresVector2);

	bool PlayerPlatformCollision(Player &player);
private:
};

#endif