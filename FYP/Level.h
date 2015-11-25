#ifndef LEVEL_H
#define LEVEL_H

#include "stdafx.h"
#include <Box2D\Box2D.h>
#include "Renderer.h"
#include <fstream>
#include <iostream> 
#include <vector>;
#include "PlatformManager.h"

class Level
{
public:
	Level();

	static void LoadLevel(std::string name, b2World* world);
	static void draw(Renderer render);
	static vector<std::string> loadALevelFromTextFile(std::string name);
private:      
	static const int SCALE;//class variable
	static int currentlevel;
	static const int MAXLEVELS;

};

#endif