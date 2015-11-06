//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#include "Menu.h"
#include "Player.h"
#include "LevelManager.h"
#include "CollisionManager.h"
#include "Score2.h"
#include "Level.h"

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
	int gameState = MENU;

	#pragma region Create class Instances

	// Player
	Player player(windowWidth, windowHeight);

	// Menu
	Menu menu(window.getViewport(window.getView()).width, window.getViewport(window.getView()).height);

	// Score2
	std::vector<Score2> scores2Vector;// A vector of score objects
	Score2 score(400, 550);
	scores2Vector.push_back(score);
	Score2 score2(450, 550);
	scores2Vector.push_back(score2);
	Score2 score3(700,200);
	scores2Vector.push_back(score3);

	// Level Manager
	LevelManager::GetInstance()->Init();

	// Level
	sf::Texture texture;
	texture.loadFromFile("Images/space.png");
	Level level(texture);

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
				cm.PlayerScoreCollision(player, scores2Vector);
				cm.PlayerPlatformCollision(player);

				// Draw
				level.DrawBackground(window);
				player.Draw(window);
				LevelManager::GetInstance()->Draw(window);

				for (std::vector<Score2>::iterator it = scores2Vector.begin(); it != scores2Vector.end(); ++it)
				{
					it->Draw(window);
				}
				break;
		}

		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}

