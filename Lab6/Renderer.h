#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <SDL.h>

class Renderer
{
private:
	static bool instanceFlag;
	static Renderer* instance;

	SDL_Renderer* gRenderer = NULL;

	int SCREEN_WIDTH, SCREEN_HEIGHT;
	int startMovingCameraPos;

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

public:
	
	static Renderer* GetInstance();
	~Renderer()
	{
		instanceFlag = false;
	}

	bool Init(SDL_Window* window ,int screen_Width, int screen_Height);

	void ClearRenderer();
	void RenderScreen();

	void DrawImage(SDL_Rect *source, SDL_Rect *dest, SDL_Texture *text, double angle, SDL_Point* centre, float zIndex);
	void DrawImageNoOffset(SDL_Rect *source, SDL_Rect *dest, SDL_Texture *text, double angle, SDL_Point* centre);

	void UpdateCameraPosition(int playerXPos);

	// Getter
	SDL_Renderer* Get_SDL_RENDERER();
	int cameraXOffSet;
};
#endif