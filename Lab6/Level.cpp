#include "stdafx.h"
#include "Level.h"

const int Level::SCALE = 32;
const int Level::MAXLEVELS = 3;

Level::Level()
{
	currentlevel = 1;
}

// This is where we load the various game entities
// e.g. platforms, pickups etc
void Level::LoadLevel(string name, b2World* world, string speedType, int width, int height)
{
	vector<string> map = Level::loadALevelFromTextFile(name);
	const int charactersAcross = map.begin()->size();
	const int charactersDown = map.size();

	int barrierCounter = 0;
	int switchCounter = 0;

	// Go through each each row
	for (int y = 0; y < charactersDown; y++)
	{
		// Go through each character of each row
		for (int x = 0; x < charactersAcross; x++)
		{
			char c = (char)map[y][x];

			if (c == 'B')// 'B' for blank
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
			}
			else if (c == 'P')// 'P' for top platform
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE*3, SCALE };
				PlatformManager::GetInstance()->addPlatform(temp, world, "topPlatform");
			}
			else if (c == 'p')// 'p' for bottom platform
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE*3, SCALE };
				PlatformManager::GetInstance()->addPlatform(temp, world, "bottomPlatform");
			}
			else if (c == 'm')// 'm' for moving platform LEFT & RIGHT
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE * 3, SCALE };
				PlatformManager::GetInstance()->addMovingPlatform(temp, world, speedType, true);
			}
			else if (c == 'D')// 'D' for moving platform UP & DOWN
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE * 3, SCALE };
				PlatformManager::GetInstance()->addMovingPlatform(temp, world, speedType, false);
			}
			else if (c == 'l')// 'l' for left sensor, used for stopping moving platform
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				PlatformManager::GetInstance()->addMovePlatSensor(temp, world, 2);
			}
			else if (c == 'r')// 'r' for left sensor, used for stopping moving platform
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				PlatformManager::GetInstance()->addMovePlatSensor(temp, world, 1);
			}
			else if (c == 'u')// 'b' for up sensor, used for stopping moving platform
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				PlatformManager::GetInstance()->addMovePlatSensor(temp, world, 3);
			}
			else if (c == 'd')// 't' for down sensor, used for stopping moving platform
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				PlatformManager::GetInstance()->addMovePlatSensor(temp, world, 4);
			}
			else if (c == 'S')// 'S' for score
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				PickupManager::GetInstance()->addScorePickups(temp, world, speedType);
			}
			else if (c == 'H')// 'H' for health
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				PickupManager::GetInstance()->addHealthPickups(temp, world);
			}
			else if (c == 'g')// 'g' for 'Machine Gun'
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, 59, SCALE };
				PickupManager::GetInstance()->addMachineGun(temp, world);
			}
			else if (c == 'M')// 'M' for Mine
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::GetInstance()->addMineObstacles(temp, world);
			}
			else if (c == 'E')// 'E' for Electric Barrier
			{
				barrierCounter += 1;
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE*3 };
				ObstacleManager::GetInstance()->addElectricBarriers(temp, world, speedType, barrierCounter);
			}
			else if (c == 'e')// 'e' for Electric Switch
			{
				switchCounter += 1;
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::GetInstance()->addElectricSwitches(temp, world, switchCounter);
			}
			else if (c == 'T')// 'T' for Teleporter
			{
				if (name == "Text/Level1.txt")
				{
					SDL_Rect temp = { x*SCALE, y*SCALE - 40, SCALE * 2 + 5, SCALE * 3 + 15 };
					Teleporter::GetInstance()->Init(temp, world, speedType);
				}
				else
				{
					SDL_Rect temp = { x*SCALE, y*SCALE - 40, SCALE * 2 + 5, SCALE * 3 + 15 };
					Teleporter::GetInstance()->SetPosition(temp);
				}
			}
			else if (c == 'W')// 'W' for Wall (This is an invisible wall which prevents the player from going off the screen)
			{
				SDL_Rect temp = { x*SCALE-20, y*SCALE, SCALE, SCALE };
				WallManager::GetInstance()->addWallParts(temp, world);
			}
			else if (c == 'G')// 'G' for Grunt(Basic enemy)
			{
				int enemyColor = (rand() % 4) + 1;
				int enemyDir = (rand() % 2) + 1;
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				EnemyManager::GetInstance()->addGrunt(temp, world, enemyColor, enemyDir, speedType, width, height);
			}
		}// End inner for loop
	}// End outer for loop
}

vector<string> Level::loadALevelFromTextFile(string name)
{
	vector<string > mystringvector;
	ifstream myfile;
	myfile.open(name);
	string c = "";
	while (myfile >> c)
	{
		mystringvector.push_back(c);
	}

	myfile.close();
	return mystringvector;
}

int Level::GetLevelNum()
{
	return currentlevel;
}

void Level::SetLevelNum(int nextLevel)
{
	currentlevel = nextLevel;
}