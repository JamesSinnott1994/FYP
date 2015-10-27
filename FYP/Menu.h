#ifndef MENU_H
#define MENU_h

class Menu
{
public:
	Menu(int windowWidth, int windowHeight);
	void Update(sf::RenderWindow &window, int windowWidth, int windowHeight, sf::Event Event);
	void CheckMouseClicked(sf::Event Event);
	void PlayButtonClicked(sf::Vector2f mousePosition, sf::RenderWindow &window, int windowWidth, int windowHeight);
	void OptionsButtonClicked(sf::Vector2f mousePosition, sf::RenderWindow &window, int windowWidth, int windowHeight);
	void ExitButtonClicked(sf::Vector2f mousePosition, sf::RenderWindow &window, int windowWidth, int windowHeight);
	void Draw(sf::RenderWindow &window);

	// Getter/Setter methods
	bool GetMouseClicked() const;
	void SetMouseClicked(bool myMouseClicked);

	bool GetPlayBtnClicked() const;
	void SetPlayBtnClicked(bool myPlayBtnClicked);
private:
	sf::Texture m_mainMenuTexture;
	sf::Sprite m_mainMenuSprite;

	sf::Texture m_playBtnNotOverTexture;
	sf::Texture m_playBtnOverTexture;
	sf::Sprite m_playButtonSprite;

	sf::Texture m_optionsBtnNotOverTexture;
	sf::Texture m_optionsBtnOverTexture;
	sf::Sprite m_optionsButtonSprite;

	sf::Texture m_exitBtnNotOverTexture;
	sf::Texture m_exitBtnOverTexture;
	sf::Sprite m_exitButtonSprite;

	bool m_mouseClicked;
	bool m_playBtnClicked;
};

#endif