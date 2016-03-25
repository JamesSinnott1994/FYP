#ifndef OBSTACLEMANAGER_H
#define OBSTACLEMANAGER_H

#include <list>
#include "Mine.h"
#include "ElectricBarrier.h"

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
	void addElectricBarriers(SDL_Rect pRect, b2World* world, string speedType);

	bool CheckMineCollision(b2Body*playerBody);
	bool CheckBarrierCollision(b2Body*playerBody);

private:
	ObstacleManager()// Constructor
	{
		// Mines
		m_mines = list<Mine*>();
		m_mineTexture = Sprite::loadTexture("Images/Mine.png", Renderer::GetInstance()->Get_SDL_RENDERER());
		m_mineSource = { 0, 0, 28, 24 };

		// Electric barriers
		m_barriers = list<ElectricBarrier*>();
		m_barrierTexture = Sprite::loadTexture("Images/ElectricBarrier.png", Renderer::GetInstance()->Get_SDL_RENDERER());
		m_barrierSource = { 0, 0, 422, 202 };
	}

	static bool instanceFlag;
	static ObstacleManager* instance;

	// Mines
	list<Mine*> m_mines;
	SDL_Texture* m_mineTexture;
	SDL_Rect m_mineSource;
	list<Mine*>::iterator m_mineIterator;

	// Electric barriers
	list<ElectricBarrier*> m_barriers;
	SDL_Texture* m_barrierTexture;
	SDL_Rect m_barrierSource;
	list<ElectricBarrier*>::iterator m_barrierIterator;
};

#endif