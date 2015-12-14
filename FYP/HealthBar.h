#ifndef HEALTHBAR_H
#define HEALTHBAR_H

class HealthBar
{
public:
	HealthBar();

	void RenderHPBar(int x, int y, int w, int h, float percent, SDL_Color FGColor, SDL_Color BGColor);
private:
};

#endif