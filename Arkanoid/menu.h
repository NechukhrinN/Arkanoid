#ifndef  MENU
#define MENU
#include "MainGame.h"
#include <vector>

class Menu
{
public:
	Menu(sf::RenderWindow* window);
	~Menu();

private:
	void layoutMenu();
	void showInfo(sf::RenderWindow* window, sf::Sprite* screen);
	void showSettings(sf::RenderWindow* window);
	void applyResolution(sf::RenderWindow* window, const sf::VideoMode& mode);

public:
	sf::Texture* helpTexture;
	sf::Texture* highscoreTexture;
	sf::Texture* aboutTexture;
	sf::Texture* menuBackground;

	sf::Sprite* help;
	sf::Sprite* about;
	sf::Sprite* menuBg;

	sf::Font* font;
	sf::Text* newGameLabel;
	sf::Text* helpLabel;
	sf::Text* aboutLabel;
	sf::Text* settingsLabel;
	sf::Text* exitLabel;
	std::vector<sf::VideoMode> resolutions;

public:
	MainGame* game;
	sf::Event* Event;

public:
	bool isMenu;
	int menuNum;
};

#endif
