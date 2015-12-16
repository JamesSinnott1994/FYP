#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H

#include <list>
#include "Mine.h"

class ObstacleManager
{
public:
	static ObstacleManager* GetInstance();
	~ObstacleManager()// Destructor
	{
		instanceFlag = false;
	}

	void Draw();
	void Update();
	void Reset();
	void Destroy();

	void addMineObstacles(SDL_Rect pRect, b2World* world);

	bool CheckMineCollision(b2Body*playerBody);

private:
	ObstacleManager()// Constructor
	{
		m_mines = list<Mine*>();
		m_mineTexture = Sprite::loadTexture("Images/Mine.png", Renderer::GetInstance()->Get_SDL_RENDERER());
		m_mineSource = { 0, 0, 28, 24 };
	}

	static bool instanceFlag;
	static ObstacleManager* instance;

	list<Mine*> m_mines;
	SDL_Texture* m_mineTexture;
	SDL_Rect m_mineSource;
	list<Mine*>::iterator m_mineIterator;
};

#endif