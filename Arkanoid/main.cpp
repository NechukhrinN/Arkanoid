#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include "menu.h"
#include "settings.h"


int main()
{
	Settings::currentResolution = Settings::highestSupportedResolution();
	Settings::displayMode = Settings::DisplayMode::Fullscreen;

	sf::RenderWindow* window = new sf::RenderWindow();
	Settings::applyWindowSettings(*window, Settings::WINDOW_TITLE);

	Menu* menu = new Menu(window);

	delete(menu);
	delete(window);
	//system("pause");
	return 0;
}
