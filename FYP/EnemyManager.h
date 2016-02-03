#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <iostream> 
#include <SDL.h>			//SDL
#include <stdio.h>
#include "SDL_mixer.h"
#include <list>
#include "Grunt.h"

using namespace std;

class EnemyManager
{
public:
	static EnemyManager* GetInstance();
	~EnemyManager()
	{
		instanceFlag = false;
	}

	void Draw();
	bool Update(SDL_Rect &playerRect, b2Body* playerBody);

	bool GruntCheckCollision(b2Body* playerBody);
	bool CheckBulletCollision(b2Body* bulletBody);

	void Reset();
	void Destroy();

	void addGrunt(SDL_Rect pRect, b2World* world, int color, int direction, string speedType, int width, int height);

	void addScoreForPlayer();

private:
	EnemyManager()
	{
		m_grunts = list<Grunt*>();
	}

	static bool instanceFlag;
	static EnemyManager* instance;

	// Grunt
	list<Grunt*> m_grunts;
	list<GruntBullet*>m_gruntBullets;
	SDL_Texture* m_gruntTexture;
	SDL_Rect m_gruntSource;
	list<Grunt*>::iterator m_gruntIterator;
	list<GruntBullet*>::iterator m_gruntBulletIterator;

};
#endif