#include "MainGame.h"

MainGame::MainGame() : restart(false), pScore(0), CurrentFrame(0), is_space(false), n(0), time(0), ball(new Ball("ball.png", 309, 435, 12, 12)),
						paddle(new Paddle("paddle_anim.png", 270, 450, 90, 9))
{
	Event = new sf::Event;
	clock_p = new sf::Clock;
	
	//Loading Fonts fot point counter end endgame message
	font = new sf::Font;
	font->loadFromFile("res/fonts/arial.ttf");
	text = new sf::Text("", *font, 20);
	text->setFillColor(sf::Color::White);
	text_begin = new sf::Text("", *font, 20);
	text_begin->setFillColor(sf::Color::Black);
	text_end = new sf::Text("", *font, 20);
	text_end->setFillColor(sf::Color::Red);

	//Loading Images of blocks and backgound
	block_image = new sf::Image;
	block_image->loadFromFile("res/images/block.png");
	backg_image = new sf::Image;
	backg_image->loadFromFile("res/images/background.jpg");

	//Loading textures of blocks and backgound from images
	block = new sf::Texture;
	block->loadFromImage(*block_image);
	backg = new sf::Texture;
	backg->loadFromImage(*backg_image);

	//Loading sprites of blocks and backgound from textures
	s_block = new sf::Sprite;
	s_block->setTexture(*block);
	s_backg = new sf::Sprite;
	s_backg->setTexture(*backg);

	/*Making array with information of position of blocks*/
	block_a = new sf::Sprite[100];
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block_a[n].setTexture(*block);
			block_a[n].setPosition(i * 55, j * 25);
			n++;
		}
	
}

bool MainGame::StartGame(sf::RenderWindow* window)
{		
	while (window->isOpen() && !restart)
	{		
		while (window->pollEvent(*Event))
		{
			if (Event->type == sf::Event::Closed)
				window->close();
		}						
		/*Timer for animation and object's movement*/
		time = static_cast<float>(clock_p->getElapsedTime().asMicroseconds());
		clock_p->restart();
		time = time / 800;

		/*Keys for restart and close game, active in game window since game start*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return false;
		
		window->clear();
		window->draw(*s_backg);
		paddle->update(time);
		window->draw(*paddle->sprite);
		ball->update();
		window->draw(*ball->sprite);		

		//Blocks drawing
		for (int i = 0; i < n; i++)
			window->draw(block_a[i]);				

		//Draw text with information about points in upper left corner
		std::ostringstream playerScoreString, gameHS;
		playerScoreString << pScore;
		text->setString("Points: " + playerScoreString.str());
		text->setPosition(0, 0);

		//Draw text with information about points in upper left corner		
		window->draw(*text);
		window->display();

		/*Game doesn't start while player don't press "Space" bottom*/
		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (is_space == false))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) return true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return false;
			ball->dx = 0;
			ball->dy = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !is_space)
		{
			ball->dx = 5 * time * 0.3;
			ball->dy = -5 * time * 0.3;
			is_space = true;
		}

		/*Ball's movement realization and ball's collision with blocks and puddle*/
		ball->x += ball->dx * 0.1;

		for (int i = 0; i < n; i++)
			/*The sprite of ball is square, to get collision with circle I need to change the border of the sprite,
			  so that the sprite of the ball is superimposed on the sprite of the block*/
			if (sf::FloatRect(ball->x + 3, ball->y + 3, 6, 6).intersects(block_a[i].getGlobalBounds()))
			{
				block_a[i].setPosition(-100, 0); ball->dx = -ball->dx; ++pScore;
			}

		ball->y += ball->dy * 0.1;

		for (int i = 0; i < n; i++)
			if (sf::FloatRect(ball->x + 3, ball->y + 3, 6, 6).intersects(block_a[i].getGlobalBounds()))
			{
				block_a[i].setPosition(-100, 0); ball->dy = -ball->dy; ++pScore;
			}

		if (sf::FloatRect(ball->x, ball->y, 12, 12).intersects(paddle->sprite->getGlobalBounds())) ball->dy = -5 * time * 0.3;

		/*"End screen" start when ball hit the bottom line of window or player get 100 point,
		  include actual score and highscore, highscore rewrite if actual score is higher
		  This information is active while "Space" key is not clicked*/
		if ((ball->y > 480) || (pScore == 100))
		{
			gameHS << get_highscore(pScore);
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				window->clear();
				window->draw(*s_backg);
				text_end->setString("End points: " + playerScoreString.str() + "\nPress space" + "\nHigh Score: " + gameHS.str());
				text_end->setPosition(260, 190);
				window->draw(*text_end);
				window->display();
			}	
		
			return false;
		}
	}
}

MainGame::~MainGame()
{
	delete(ball);
	delete(paddle);

	delete(font);

	delete(text);
	delete(text_begin);
	delete(text_end);

	delete(clock_p);

	delete(s_backg);
	delete(s_block);
	delete[](block_a);
	
	delete(block_image);
	delete(backg_image);

	delete(block);
	delete(backg);	
}