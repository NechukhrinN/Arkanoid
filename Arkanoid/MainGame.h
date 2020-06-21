#ifndef  MAINGAME
#define MAINGAME
#include <SFML\Graphics.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include "highscore.h"
#include "ball.h"
#include "paddle.h"

class MainGame
{
public:
	MainGame();
	bool StartGame(sf::RenderWindow* window);	
	~MainGame();

public:
	bool restart;
	int pScore;
	float CurrentFrame;
	bool is_space;
	int n;	

	Ball* ball;
	Paddle* paddle;
	
	sf::Event* Event;

	sf::Font* font;

	sf::Text* text;
	sf::Text* text_begin;
	sf::Text* text_end;
	
	sf::Clock* clock_p;
	
	sf::Sprite* s_backg;
	sf::Sprite* s_block;
	

	sf::Image* block_image;
	sf::Image* backg_image;
	
	sf::Texture* block;
	sf::Texture* backg;	

	sf::Sprite* block_a;

public:
	float time;	
};

typedef std::unique_ptr<MainGame> MainGame_ptr;

#endif