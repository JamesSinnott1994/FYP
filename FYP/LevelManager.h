#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Level.h"

class LevelManager
{
public:
	void Init();
	void Draw(sf::RenderWindow &window);
	void Update();

	static LevelManager* GetInstance();

	~LevelManager()
	{
		instanceFlag = false;
	}
private:
	LevelManager()
	{
		levels = std::list<Level>();
	}
	std::list<Level> levels;
	static bool instanceFlag;
	static LevelManager* instance;
};

#endif