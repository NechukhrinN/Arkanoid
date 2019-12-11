#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
#include "menu.h"


int main()
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(640, 480), "Arkanoid by Nikita Nechukhrin");
	menu(*window);
	window->setFramerateLimit(60);
	//system("pause");
	return 0;
}
