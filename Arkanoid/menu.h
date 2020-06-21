#ifndef  MENU
#define MENU
#include "MainGame.h"

class Menu
{
public:
	Menu(sf::RenderWindow* window);
	~Menu();

public:
	sf::Texture* menuTexture1;
	sf::Texture* menuTexture2;
	sf::Texture* menuTexture3;
	sf::Texture* menuTexture4;
	sf::Texture* helpTexture;
	sf::Texture* highscoreTexture;
	sf::Texture* aboutTexture;
	sf::Texture* menuBackground;

	sf::Sprite* menu1;
	sf::Sprite* menu2;
	sf::Sprite* menu3;
	sf::Sprite* menu4;
	sf::Sprite* help;
	sf::Sprite* about;
	sf::Sprite* menuBg;

public:
	MainGame* game;
	sf::Event* Event;

public:
	bool isMenu;
	int menuNum;
};

#endif