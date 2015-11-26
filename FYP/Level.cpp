#include "stdafx.h"
#include "Level.h"

const int Level::SCALE = 32;
const int Level::MAXLEVELS = 3;
int Level::currentlevel = 0;

Level::Level()
{
	currentlevel = 0;
}

// This is where we load the various game entities
// e.g. platforms, pickups etc
void Level::LoadLevel(string name, b2World* world)
{
	vector<string> map = Level::loadALevelFromTextFile(name);
	const int charactersAcross = 34;
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

		}// End inner for loop
	}// End outer for loop
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