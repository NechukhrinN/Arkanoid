#ifndef  MENU
#define MENU
#include <SFML\Graphics.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include "highscore.h"

void menu(sf::RenderWindow & window);

bool startGame(sf::RenderWindow& window);

void gameRunning(sf::RenderWindow& window);

#endif