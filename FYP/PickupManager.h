#ifndef PICKUPMANAGER_H
#define PICKUPMANAGER_H

#include <list>
#include "Score.h"
#include "Health.h"

class PickupManager
{
public:
	static PickupManager* GetInstance();
	~PickupManager()
	{
		instanceFlag = false;
	}

	void Draw();
	void Update();
	void Reset();

	void addScorePickups(SDL_Rect pRect, b2World* world);
	void addHealthPickups(SDL_Rect pRect, b2World* world);

	bool CheckScoreCollision(b2Body*playerBody);
	bool CheckHealthCollision(b2Body*playerBody);

private:
	PickupManager()
	{
		m_scores = list<Score*>();
		m_scoreTexture = Sprite::loadTexture("Images/Score.png", Renderer::GetInstance()->Get_SDL_RENDERER());
		m_scoreSource = { 0, 0, 91, 91 };

		m_healthPickups = list<Health*>();
		m_healthTexture = Sprite::loadTexture("Images/HealthPickup.png", Renderer::GetInstance()->Get_SDL_RENDERER());
		m_healthSource = { 0, 0, 99, 100 };
	}

	static bool instanceFlag;
	static PickupManager* instance;

	list<Score*> m_scores;
	SDL_Texture* m_scoreTexture;
	SDL_Rect m_scoreSource;
	list<Score*>::iterator m_scoreIterator;

	list<Health*> m_healthPickups;
	SDL_Texture* m_healthTexture;
	SDL_Rect m_healthSource;
	list<Health*>::iterator m_healthIterator;
};

#endif

