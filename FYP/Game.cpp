//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#include "Menu.h"
#include "Player.h"
#include "LevelManager.h"
#include "CollisionManager.h"

////////////////////////////////////////////////////////////
///Entrypoint of application 
//////////////////////////////////////////////////////////// 

int main()
{
	// Render window width and height
	int windowWidth = 800;
	int windowHeight = 600;

	// Create the main window 
	sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight, 32), "SFML First Program");
	window.setFramerateLimit(60);

	// Game states
	const int MENU = 0, PLAY = 1;
	int gameState = PLAY;

	#pragma region Create class Instances

	// Player
	Player player(windowWidth, windowHeight);

	// Menu
	Menu menu(window.getViewport(window.getView()).width, window.getViewport(window.getView()).height);

	// Level Manager
	LevelManager::GetInstance()->Init();

	// Collision Manager
	CollisionManager cm;

	#pragma endregion

	// Start game loop 
	while (window.isOpen())
	{
		// Process events 
		sf::Event Event;
		while (window.pollEvent(Event))
		{
			// Close window : exit 
			if (Event.type == sf::Event::Closed)
				window.close();

			// Escape key : exit 
			if ((Event.type == sf::Event::KeyPressed) && (Event.key.code == sf::Keyboard::Escape))
				window.close();
		}

		//prepare frame
		window.clear();

		// For switching between game states
		switch (gameState)
		{
			case MENU:
				// Update
				menu.Update(window, window.getViewport(window.getView()).width, window.getViewport(window.getView()).height, Event);

				if (menu.GetPlayBtnClicked())
				{
					gameState = PLAY;
				}
				
				// Draw
				menu.Draw(window);
				break;

			case PLAY:
				// Update
				player.Update(Event);
				cm.PlayerScoreCollision();

				// Draw
				player.Draw(window);
				LevelManager::GetInstance()->Draw(window);
				break;
		}

		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}

