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
void Level::LoadLevel(string name, b2World* world, string speedType)
{
	vector<string> map = Level::loadALevelFromTextFile(name);
	const int charactersAcross = 72;
	const int charactersDown = 20;

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
			else if (c == 'S')// 'S' for score
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				PickupManager::GetInstance()->addScorePickups(temp, world);
			}
			else if (c == 'H')// 'H' for health
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				PickupManager::GetInstance()->addHealthPickups(temp, world);
			}
			else if (c == 'M')// 'M' for Mine
			{
				SDL_Rect temp = { x*SCALE, y*SCALE, SCALE, SCALE };
				ObstacleManager::GetInstance()->addMineObstacles(temp, world);
			}
			else if (c == 'T')// 'T' for Teleporter
			{
				if (name == "Text/Level1.txt")
				{
					SDL_Rect temp = { x*SCALE, y*SCALE - 55, SCALE * 2 + 5, SCALE * 3 + 15 };
					Teleporter::GetInstance()->Init(temp, world);
				}
				else
				{
					SDL_Rect temp = { x*SCALE, y*SCALE - 55, SCALE * 2 + 5, SCALE * 3 + 15 };
					Teleporter::GetInstance()->SetPosition(temp);
				}
			}

		}// End inner for loop
	}// End outer for loop

	int t = 0;
}

void Level::draw(Renderer Render)
{
	
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