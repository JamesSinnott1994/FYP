#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"
#include <Box2D\Box2D.h>
#include "Renderer.h"
#include <fstream>
#include <iostream> 
#include <vector>;
#include "PlatformManager.h"
#include "PickupManager.h"
#include "ObstacleManager.h"
#include "Teleporter.h"
#include "WallManager.h"
#include "EnemyManager.h"

class Level
{
public:
	Level();

	static void LoadLevel(std::string name, b2World* world, string speedType, int width, int height);
	static vector<std::string> loadALevelFromTextFile(std::string name);

	int GetLevelNum();
	void SetLevelNum(int);
private:      
	static const int SCALE;//class variable
	int currentlevel;
	static const int MAXLEVELS;
};

#endif