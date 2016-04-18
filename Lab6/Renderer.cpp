#include "stdafx.h"
#include <Renderer.h>

bool Renderer::instanceFlag = false;
Renderer* Renderer::instance = NULL;

Renderer* Renderer::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new Renderer;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

/*
Sets up our renderer
*/
bool Renderer::Init(SDL_Window* window ,int screen_Width, int screen_Height)
{
	// Create Renderer for the Window
	gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SCREEN_WIDTH = screen_Width;
	SCREEN_HEIGHT = screen_Height;

	startMovingCameraPos = 300;

	if (gRenderer == NULL)
	{
		printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else
	{
		//Initialize renderer color
		SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		screenSurface = SDL_GetWindowSurface(window);
	}
	return true;
}

/*
Draws images offset from the camera
*/
void Renderer::DrawImage(SDL_Rect *source, SDL_Rect *dest, SDL_Texture *text, double angle, SDL_Point* centre, float zIndex) 
{
	// Determines whether sprite rectangle is on screen
	if ((dest->x + dest->w > cameraXOffSet) && (dest->x < cameraXOffSet + SCREEN_WIDTH))
	{
		SDL_RendererFlip flip = SDL_FLIP_NONE;

		// Sprite rectangle position
		SDL_Rect offSetRect = { dest->x - cameraXOffSet / zIndex, dest->y, dest->w, dest->h };

		SDL_RenderCopyEx(gRenderer, text, source, &offSetRect, angle, centre, flip);// Copy the image to the rendering object.
	}
}
void Renderer::DrawImageNoOffset(SDL_Rect *source, SDL_Rect *dest, SDL_Texture *text, double angle, SDL_Point* centre) 
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	SDL_RenderCopyEx(gRenderer, text, source, dest, angle, centre, flip);//Copy the image to the rendering object.
}

void Renderer::ClearRenderer()
{
	// Sets colour that we're clearing the screen with
	SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, 0);

	// This clears the screen
	SDL_RenderClear(gRenderer);

}

void Renderer::RenderScreen()
{
	SDL_RenderPresent(gRenderer);
}

void Renderer::UpdateCameraPosition(int playerXPos)
{
	if (playerXPos > startMovingCameraPos) // Move camera
	{
		cameraXOffSet = playerXPos - startMovingCameraPos;
	}
	else // Camera stays at it's initial position
	{
		cameraXOffSet = 1;
	}
}

// Getter
SDL_Renderer* Renderer::Get_SDL_RENDERER()
{
	return gRenderer;
}