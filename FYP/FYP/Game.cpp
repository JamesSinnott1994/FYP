//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#include "Menu.h"

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

	// Game states
	const int MENU = 0, PLAY = 1;
	int gameState = MENU;

	// Menu
	Menu menu(window.getViewport(window.getView()).width, window.getViewport(window.getView()).height);

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
				
				// Draw
				menu.Draw(window);

			case PLAY:
				break;
		}

		// Finally, display rendered frame on screen 
		window.display();
	} //loop back for next frame

	return EXIT_SUCCESS;
}

