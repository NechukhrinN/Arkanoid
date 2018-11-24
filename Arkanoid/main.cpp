#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <time.h>
//#include "map.h"
using namespace sf;

int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid!");
	sf:View view;
	view.reset(sf::FloatRect(0, 0, 640, 480));
	//window.setFramerateLimit(60);

	float CurrentFrame = 0;
	sf::Clock clock;
	sf::Clock gameTimeClock;
	int gameTime = 0;

	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");
	sf::Text text("", font, 20);
	text.setFillColor(Color::White);
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	Image map_image;
	map_image.loadFromFile("images/map.png");
	Image ball_image;
	ball_image.loadFromFile("images/ball_anim.png");
	Image paddle_image;
	paddle_image.loadFromFile("images/paddle_anim.png");
	Image block_image;
	block_image.loadFromFile("images/block.png");

	Texture map;
	map.loadFromImage(map_image);
	Texture ball;
	ball.loadFromImage(ball_image);
	Texture paddle;
	paddle.loadFromImage(paddle_image);
	Texture block;
	block.loadFromImage(block_image);

	Sprite s_map;
	s_map.setTexture(map);
	Sprite s_ball;
	s_ball.setTexture(ball);
	Sprite s_paddle;
	s_paddle.setTexture(paddle);
	s_paddle.setTextureRect(IntRect(0, 0, 90, 9));
	Sprite s_block;
	s_block.setTexture(block);
	
	s_paddle.setPosition(270, 450);

	Sprite block_a[1000];

	int n = 0;
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block_a[n].setTexture(block);
			block_a[n].setPosition(i * 55, j * 25);
			n++;
		}
	
	while (window.isOpen())
	{
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();
		}
		
		//std::ostringstream playerScoreString, gameTimeString;
		//playerScoreString << p.pScore;
		//gameTimeString << gameTime;
		text.setString("Points: ");
		text.setPosition(0,0);


		window.draw(s_paddle);

		for (int i = 0; i < n; i++)
			window.draw(block_a[i]);

		window.draw(text);
		window.display();
	}

	return 0;
}
