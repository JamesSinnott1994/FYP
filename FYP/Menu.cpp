#include "stdafx.h"
#include "Menu.h"

Menu::Menu(int windowWidth, int windowHeight)
{
	// Load main menu background image
	m_mainMenuTexture.loadFromFile("Images/MainMenuBackground.jpg");
	m_mainMenuSprite = sf::Sprite(m_mainMenuTexture);

	// Scale image to window
	m_mainMenuSprite.setScale(windowWidth / m_mainMenuSprite.getLocalBounds().width, 
		windowHeight / m_mainMenuSprite.getLocalBounds().height);

	#pragma region Setup Buttons

		// Load buttons
		m_playBtnNotOverTexture.loadFromFile("Images/PlayBtnNotOver.png");
		m_playBtnOverTexture.loadFromFile("Images/PlayBtnOver.png");
		m_playButtonSprite = sf::Sprite(m_playBtnNotOverTexture);
		m_playButtonSprite.setPosition(sf::Vector2f((windowWidth / 2) - (m_playButtonSprite.getLocalBounds().width / 2),
			windowHeight*0.75f));

		m_optionsBtnNotOverTexture.loadFromFile("Images/OptionsBtnNotOver.png");
		m_optionsBtnOverTexture.loadFromFile("Images/OptionsBtnOver.png");
		m_optionsButtonSprite = sf::Sprite(m_optionsBtnNotOverTexture);
		m_optionsButtonSprite.setPosition(sf::Vector2f((windowWidth * 0.2f) - (m_optionsButtonSprite.getLocalBounds().width / 2),
			windowHeight*0.8f));

		m_exitBtnNotOverTexture.loadFromFile("Images/ExitBtnNotOver.png");
		m_exitBtnOverTexture.loadFromFile("Images/ExitBtnOver.png");
		m_exitButtonSprite = sf::Sprite(m_exitBtnNotOverTexture);
		m_exitButtonSprite.setPosition(sf::Vector2f((windowWidth * 0.8f) - (m_exitButtonSprite.getLocalBounds().width / 2),
			windowHeight*0.8f));

		// Scale buttons according to window size
		m_playButtonSprite.setScale(windowWidth*0.00125f, windowHeight*0.00125f);
		m_optionsButtonSprite.setScale(windowWidth*0.00125f, windowHeight*0.00125f);
		m_exitButtonSprite.setScale(windowWidth*0.00125f, windowHeight*0.00125f);

	#pragma endregion

	// Booleans
	m_mouseClicked = false;
	m_playBtnClicked = false;
}

void Menu::Update(sf::RenderWindow &window, int windowWidth, int windowHeight, sf::Event Event)
{
	sf::Vector2f mousePosition = sf::Vector2f((float)sf::Mouse::getPosition(window).x, (float)sf::Mouse::getPosition(window).y);

	CheckMouseClicked(Event);
	PlayButtonClicked(mousePosition, window, windowWidth, windowHeight);
	OptionsButtonClicked(mousePosition, window, windowWidth, windowHeight);
	ExitButtonClicked(mousePosition, window, windowWidth, windowHeight);
}

void Menu::CheckMouseClicked(sf::Event Event)
{
	if (Event.type == sf::Event::MouseButtonPressed)
	{
		SetMouseClicked(true);
	}
	if (Event.type == sf::Event::MouseButtonReleased)
	{
		SetMouseClicked(false);
	}
}

#pragma region Button Clicked Methods

// Checks if mouse is over button and if button is clicked
void Menu::PlayButtonClicked(sf::Vector2f mousePosition, sf::RenderWindow &window, int windowWidth, int windowHeight)
{
	if (mousePosition.x >= m_playButtonSprite.getGlobalBounds().left
		&& mousePosition.x <= m_playButtonSprite.getGlobalBounds().left + m_playButtonSprite.getGlobalBounds().width
		&& mousePosition.y >= m_playButtonSprite.getGlobalBounds().top
		&& mousePosition.y <= m_playButtonSprite.getGlobalBounds().top + m_playButtonSprite.getGlobalBounds().height
		&& GetMouseClicked() == false)
	{
		m_playButtonSprite = sf::Sprite(m_playBtnOverTexture);
		m_playButtonSprite.setPosition(sf::Vector2f((windowWidth / 2) - (m_playButtonSprite.getLocalBounds().width / 2),
			windowHeight*0.75f));
		m_playButtonSprite.setScale(windowWidth*0.00125f, windowHeight*0.00125f);
	}
	else if (mousePosition.x >= m_playButtonSprite.getGlobalBounds().left
		&& mousePosition.x <= m_playButtonSprite.getGlobalBounds().left + m_playButtonSprite.getGlobalBounds().width
		&& mousePosition.y >= m_playButtonSprite.getGlobalBounds().top
		&& mousePosition.y <= m_playButtonSprite.getGlobalBounds().top + m_playButtonSprite.getGlobalBounds().height
		&& GetMouseClicked() == true)
	{
		SetPlayBtnClicked(true);
	}
	else
	{
		m_playButtonSprite = sf::Sprite(m_playBtnNotOverTexture);
		m_playButtonSprite.setPosition(sf::Vector2f((windowWidth / 2) - (m_playButtonSprite.getLocalBounds().width / 2),
			windowHeight*0.75f));
		m_playButtonSprite.setScale(windowWidth*0.00125f, windowHeight*0.00125f);
	}
}

// Checks if mouse is over button and if button is clicked
void Menu::OptionsButtonClicked(sf::Vector2f mousePosition, sf::RenderWindow &window, int windowWidth, int windowHeight)
{
	if (mousePosition.x >= m_optionsButtonSprite.getGlobalBounds().left
		&& mousePosition.x <= m_optionsButtonSprite.getGlobalBounds().left + m_optionsButtonSprite.getGlobalBounds().width
		&& mousePosition.y >= m_optionsButtonSprite.getGlobalBounds().top
		&& mousePosition.y <= m_optionsButtonSprite.getGlobalBounds().top + m_optionsButtonSprite.getGlobalBounds().height
		&& GetMouseClicked() == false)
	{
		m_optionsButtonSprite = sf::Sprite(m_optionsBtnOverTexture);
		m_optionsButtonSprite.setPosition(sf::Vector2f((windowWidth * 0.2f) - (m_optionsButtonSprite.getLocalBounds().width / 2),
			windowHeight*0.8f));
		m_optionsButtonSprite.setScale(windowWidth*0.00125f, windowHeight*0.00125f);
	}
	else if (mousePosition.x >= m_optionsButtonSprite.getGlobalBounds().left
		&& mousePosition.x <= m_optionsButtonSprite.getGlobalBounds().left + m_optionsButtonSprite.getGlobalBounds().width
		&& mousePosition.y >= m_optionsButtonSprite.getGlobalBounds().top
		&& mousePosition.y <= m_optionsButtonSprite.getGlobalBounds().top + m_optionsButtonSprite.getGlobalBounds().height
		&& GetMouseClicked() == true)
	{
		window.close();
	}
	else
	{
		m_optionsButtonSprite = sf::Sprite(m_optionsBtnNotOverTexture);
		m_optionsButtonSprite.setPosition(sf::Vector2f((windowWidth * 0.2f) - (m_optionsButtonSprite.getLocalBounds().width / 2),
			windowHeight*0.8f));
		m_optionsButtonSprite.setScale(windowWidth*0.00125f, windowHeight*0.00125f);
	}
}

// Checks if mouse is over button and if button is clicked
void Menu::ExitButtonClicked(sf::Vector2f mousePosition, sf::RenderWindow &window, int windowWidth, int windowHeight)
{
	if (mousePosition.x >= m_exitButtonSprite.getGlobalBounds().left
		&& mousePosition.x <= m_exitButtonSprite.getGlobalBounds().left + m_exitButtonSprite.getGlobalBounds().width
		&& mousePosition.y >= m_exitButtonSprite.getGlobalBounds().top
		&& mousePosition.y <= m_exitButtonSprite.getGlobalBounds().top + m_exitButtonSprite.getGlobalBounds().height
		&& GetMouseClicked() == false)
	{
		m_exitButtonSprite = sf::Sprite(m_exitBtnOverTexture);
		m_exitButtonSprite.setPosition(sf::Vector2f((windowWidth * 0.8f) - (m_exitButtonSprite.getLocalBounds().width / 2),
			windowHeight*0.8f));
		m_exitButtonSprite.setScale(windowWidth*0.00125f, windowHeight*0.00125f);
	}
	else if (mousePosition.x >= m_exitButtonSprite.getGlobalBounds().left
		&& mousePosition.x <= m_exitButtonSprite.getGlobalBounds().left + m_exitButtonSprite.getGlobalBounds().width
		&& mousePosition.y >= m_exitButtonSprite.getGlobalBounds().top
		&& mousePosition.y <= m_exitButtonSprite.getGlobalBounds().top + m_exitButtonSprite.getGlobalBounds().height
		&& GetMouseClicked() == true)
	{
		window.close();
	}
	else
	{
		m_exitButtonSprite = sf::Sprite(m_exitBtnNotOverTexture);
		m_exitButtonSprite.setPosition(sf::Vector2f((windowWidth * 0.8f) - (m_exitButtonSprite.getLocalBounds().width / 2),
			windowHeight*0.8f));
		m_exitButtonSprite.setScale(windowWidth*0.00125f, windowHeight*0.00125f);
	}
}

#pragma endregion

void Menu::Draw(sf::RenderWindow &window)
{
	window.draw(m_mainMenuSprite);
	window.draw(m_playButtonSprite);
	window.draw(m_optionsButtonSprite);
	window.draw(m_exitButtonSprite);
}

// Getter/Setter methods
bool Menu::GetMouseClicked() const
{
	return m_mouseClicked;
}

void Menu::SetMouseClicked(bool myMouseClicked)
{
	m_mouseClicked = myMouseClicked;
}

bool Menu::GetPlayBtnClicked() const
{
	return m_playBtnClicked;
}

void Menu::SetPlayBtnClicked(bool myPlayBtnClicked)
{
	m_playBtnClicked = myPlayBtnClicked;
}