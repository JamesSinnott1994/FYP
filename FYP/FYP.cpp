// FYP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// Classes
#include "Renderer.h"
#include "KeyBoardInput.h"
#include "Sprite.h"
#include "Menu.h"
#include "Play.h"
#include "SoundManager.h"

// Window width and height
const int windowWidth = 800;
const int windowHeight = 600;

// Construct a world object, which will hold and simulate the rigid bodies.
b2Vec2 gravity(0.0f, 0.1f);
b2World* world = new b2World(gravity);// = new b2World(gravity);

// Class instances
Menu* menu;
Play* play;

// Methods
void Init();

int _tmain(int argc, _TCHAR* argv[])
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	//The window we'll be rendering to
	SDL_Window* window = NULL;

	// Game state
	const int MENU = 0, PLAY = 1;
	int gameState = PLAY;


	//SDL
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create Renderer for the Window
			if (!Renderer::GetInstance()->Init(window, windowWidth, windowHeight))
			{
				return 0;
			}

			bool quit = false;

			// Initialize classes
			Init();

			SDL_Event e;
			while (!quit)
			{
				// Update keyboard
				while (SDL_PollEvent(&e) != 0)
				{
					KeyBoardInput::GetInstance()->updateKeyboard(e);
					switch (e.type)
					{
						case SDL_QUIT:
							quit = true;
							break;
					}
				}

				// Switch between game states
				switch (gameState)
				{
				case MENU:
					menu->Draw();
					if (menu->Update(e) == 3)// Exit button clicked
						quit = true;
					else if (menu->Update(e) == 1)// Play button clicked
						gameState = PLAY;
					break;

				case PLAY:
					play->Draw();
					play->Update();
					break;
				}

				// Escape button
				if (KeyBoardInput::GetInstance()->isKeyPressed(SDLK_ESCAPE))
				{
					quit = true;
				}
			}// End while
		}// End inner else
	}// End outer else

	return 0;
}

void Init()
{
	menu = new Menu(windowWidth, windowHeight);
	play = new Play(world, windowWidth, windowHeight);

	if (!SoundManager::GetInstance()->load_files())
	{
		printf("Sounds Did not load ");
	}
}

