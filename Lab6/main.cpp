#include "stdafx.h"
#include "Renderer.h"
#include "KeyBoardInput.h"
#include "Sprite.h"
#include "Menu.h"
#include "Options.h"
#include "Instructions.h"
#include "Play.h"
#include "SoundManager.h"
#include "Splash.h"
#include "GameOver.h"
#include "EnterNameScreen.h"
#include "HighScoreScreen.h"
#include <time.h>

// Window width and height
const int windowWidth = 800;
const int windowHeight = 600;

// Construct a world object, which will hold and simulate the rigid bodies.
b2Vec2 gravity(0.0f, 0.1f);
b2World* world = new b2World(gravity);

// Class instances
Menu* menu;
Options* options;
Instructions* instructions;
Play* play;
Splash* splash;
GameOver* gameOver;
EnterNameScreen* enterNameScreen;
HighScoreScreen* highScoreScreen;
bool playInitial = false;

// Methods
void Init();

int _tmain(int argc, _TCHAR* argv[])
{
	// initialize random seed
	srand(time(NULL));

	// Enable highscore table
	bool highscoreEnabled = false;

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	// The window we'll be rendering to
	SDL_Window* window = NULL;

	// Game state
	const int MENU = 0, OPTIONS = 1, INSTRUCTIONS = 2, PLAY = 3, GAMEOVER = 4, ENTER_NAME_SCREEN = 5, HIGH_SCORE_SCREEN = 6;
	int gameState = MENU;
	int returnedType;

	//SDL
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
			// Create Renderer for the Window
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
				}

				// Switch between game states
				switch (gameState)
				{
				case MENU:
					menu->Draw();
					if (menu->Update(e) == 3)// Exit button clicked
						quit = true;
					else if (menu->Update(e) == 2)// Options button clicked
						gameState = OPTIONS;
					else if (menu->Update(e) == 1)// Play button clicked
					{
						if (highscoreEnabled)
							gameState = ENTER_NAME_SCREEN;// ********************************
						else
							gameState = INSTRUCTIONS;
					}
					break;

				case OPTIONS:
					options->Draw();
					if (options->Update(e) == 1)// Back button clicked
						gameState = MENU;
					break;

				case INSTRUCTIONS:
					instructions->Draw();
					if (instructions->Update() == 1)
					{
						if (playInitial)
							play->Init(world, windowWidth, windowHeight, splash);
						gameState = PLAY;
					}
					break;

				case PLAY:
					play->Draw();
					returnedType = play->Update(e);
					if (returnedType == 2)
					{
						play->Quit();
						playInitial = true;// Used whenever we exit out of a game so that we can re-initialize the game
						gameState = MENU;
					}
					if (returnedType == 3)// Lose game
					{
						gameState = GAMEOVER;
					}
					break;

				case GAMEOVER:
					gameOver->Draw();
					if (gameOver->Update(enterNameScreen->GetName(), highScoreScreen, play->GetScore(), highscoreEnabled) == 1)
					{
						if (highscoreEnabled)
							gameState = HIGH_SCORE_SCREEN;
						else
						{
							play->Quit();
							playInitial = true;// Used whenever we exit out of a game so that we can re-initialize the game
							gameState = MENU;
						}
					}
					break;

				case ENTER_NAME_SCREEN:
					enterNameScreen->Draw();
					if (enterNameScreen->Update() == 1)
					{
						gameState = INSTRUCTIONS;
					}
					break;

				case HIGH_SCORE_SCREEN:
					highScoreScreen->Draw();
					if (highScoreScreen->Update() == 1)
					{
						play->Quit();
						playInitial = true;// Used whenever we exit out of a game so that we can re-initialize the game
						gameOver->SetScoreAddedToDatabase(false);
						gameState = MENU;
					}
					break;
				}
			}// End while
		}// End inner else
	}// End outer else

	return 0;
}

void Init()
{
	menu = new Menu(windowWidth, windowHeight);
	options = new Options(windowWidth, windowHeight);
	instructions = new Instructions(windowWidth, windowHeight);
	splash = new Splash(windowWidth, windowHeight);
	play = new Play(world, windowWidth, windowHeight, splash);
	gameOver = new GameOver(windowWidth, windowHeight);
	enterNameScreen = new EnterNameScreen(windowWidth, windowHeight);
	highScoreScreen = new HighScoreScreen(windowWidth, windowHeight);

	if (!SoundManager::GetInstance()->load_files())
	{
		printf("Sounds Did not load ");
	}
}