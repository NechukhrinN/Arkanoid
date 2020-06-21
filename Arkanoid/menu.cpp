#include "menu.h"


Menu::Menu(sf::RenderWindow* window)
{
	game = nullptr;
	//game = new MainGame();
	Event = new sf::Event;
	/*Loading bottom's sprites and set bottom's position*/
	menuTexture1 = new sf::Texture;
	menuTexture2 = new sf::Texture;
	menuTexture3 = new sf::Texture;
	menuTexture4 = new sf::Texture;
	helpTexture = new sf::Texture;
	highscoreTexture = new sf::Texture;
	aboutTexture = new sf::Texture;
	menuBackground = new sf::Texture;

	menuTexture1->loadFromFile("res/images/ngame.png");
	menuTexture2->loadFromFile("res/images/help_m.png");
	menuTexture3->loadFromFile("res/images/about_m.png");
	menuTexture4->loadFromFile("res/images/exit.png");
	helpTexture->loadFromFile("res/images/help.png");
	aboutTexture->loadFromFile("res/images/about.png");
	menuBackground->loadFromFile("res/images/main_back.jpg");

	menu1 = new sf::Sprite(*menuTexture1);
	menu2 = new sf::Sprite(*menuTexture2);
	menu3 = new sf::Sprite(*menuTexture3);
	menu4 = new sf::Sprite(*menuTexture4);
	help = new sf::Sprite(*helpTexture);
	about = new sf::Sprite(*aboutTexture);
	menuBg = new sf::Sprite(*menuBackground);

	isMenu = 1;
	menuNum = 0;
	window->draw(*menuBg);
	menu1->setPosition(100, 30);
	menu2->setPosition(100, 90);
	menu3->setPosition(100, 150);
	menu4->setPosition(100, 210);

	while (isMenu)
	{		
		while (window->pollEvent(*Event))
		{
			if (Event->type == sf::Event::Closed)
				window->close();
		}

		menu1->setColor(sf::Color::White);
		menu2->setColor(sf::Color::White);
		menu3->setColor(sf::Color::White);
		menu4->setColor(sf::Color::White);
		menuNum = 0;
		window->clear(sf::Color(129, 181, 221));

		/*Activation of the backlight when you hover the mouse*/
		if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(*window))) {
			menu1->setColor(sf::Color::Blue);
			menuNum = 1;
		}
		if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(*window))) {
			menu2->setColor(sf::Color::Blue);
			menuNum = 2;
		}
		if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(*window))) {
			menu3->setColor(sf::Color::Blue);
			menuNum = 3;
		}
		if (sf::IntRect(100, 210, 300, 50).contains(sf::Mouse::getPosition(*window))) {
			menu4->setColor(sf::Color::Blue);
			menuNum = 4;
		}

		window->draw(*menuBg);
		window->draw(*menu1);
		window->draw(*menu2);
		window->draw(*menu3);
		window->draw(*menu4);

		window->display();
			
		/*Click processing*/
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) 
			{						
				game = new MainGame();
				game->StartGame(window);				
				delete(game);
			}
			if (menuNum == 2) { window->draw(*help);	window->display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
			if (menuNum == 3) { window->draw(*about);	window->display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
			if (menuNum == 4) { window->close(); isMenu = false; }
		}

	}
}

//Reverce to restart game
//void gameRunning(sf::RenderWindow& window)
//{
//	if (startGame(window)) gameRunning(window);
//}

Menu::~Menu() 
{		
	delete(game);
	delete(Event);

	delete(menuTexture1);
	delete(menuTexture2);
	delete(menuTexture3);
	delete(menuTexture4);
	delete(helpTexture);
	delete(highscoreTexture);
	delete(aboutTexture);
	delete(menuBackground);

	delete(menu1);
	delete(menu2);
	delete(menu3);
	delete(menu4);
	delete(help);
	delete(about);
	delete(menuBg);
};
