#include "MainGame.h"
#include "settings.h"

namespace
{
	//Virtual pixels per second, independent of the frame rate.
	const float BALL_SPEED = 187.5f;
	const float MAX_FRAME_TIME = 0.05f;
}

MainGame::MainGame() : restart(false), pScore(0), CurrentFrame(0), is_space(false), n(0), time(0), ball(new Ball("ball.png", 309, 435, 12, 12)),
						paddle(new Paddle("paddle_anim.png", 270, 450, 90, 9))
{
	Event = new sf::Event;
	clock_p = new sf::Clock;
	
	const unsigned int fontSize = static_cast<unsigned int>(20 * Settings::textScale());

	//Loading Fonts fot point counter end endgame message
	font = new sf::Font;
	font->loadFromFile("res/fonts/arial.TTF");
	text = new sf::Text("", *font, fontSize);
	text->setFillColor(sf::Color::White);
	text_begin = new sf::Text("", *font, fontSize);
	text_begin->setFillColor(sf::Color::Black);
	text_end = new sf::Text("", *font, fontSize);
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
	s_block->setScale(Settings::scaleX, Settings::scaleY);
	s_backg = new sf::Sprite;
	s_backg->setTexture(*backg);
	s_backg->setPosition(0.f, 0.f);
	s_backg->setScale(Settings::scaleX, Settings::scaleY);

	/*Making array with information of position of blocks*/
	block_a = new sf::Sprite[100];
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block_a[n].setTexture(*block);
			block_a[n].setScale(Settings::scaleX, Settings::scaleY);
			block_a[n].setPosition(Settings::position(i * 55, j * 25));
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
		/*Delta time in seconds - movement is the same at any refresh rate*/
		time = clock_p->restart().asSeconds();
		if (time > MAX_FRAME_TIME)
			time = MAX_FRAME_TIME;

		/*Keys for restart and close game, active in game window since game start*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return false;

		/*The paddle can be moved before the ball is launched*/
		paddle->update(time);

		if (!is_space)
		{
			/*Keep the ball on top of the paddle until Space is pressed*/
			ball->x = paddle->getpaddlecoordinateX() + (paddle->w - ball->w) / 2.f;
			ball->y = paddle->getpaddlecoordinateY() - 15.f;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				ball->dx = BALL_SPEED;
				ball->dy = -BALL_SPEED;
				is_space = true;
				//Start timing from the moment of launch.
				clock_p->restart();
			}
		}
		else
		{
			/*Ball's movement realization and ball's collision with blocks and puddle*/
			ball->x += ball->dx * time;

			for (int i = 0; i < n; i++)
				/*The sprite of ball is square, to get collision with circle I need to change the border of the sprite,
				  so that the sprite of the ball is superimposed on the sprite of the block*/
				if (Settings::toScreenRect(ball->x + 3, ball->y + 3, 6, 6).intersects(block_a[i].getGlobalBounds()))
				{
					block_a[i].setPosition(Settings::position(-1000, 0)); ball->dx = -ball->dx; ++pScore;
				}

			ball->y += ball->dy * time;

			for (int i = 0; i < n; i++)
				if (Settings::toScreenRect(ball->x + 3, ball->y + 3, 6, 6).intersects(block_a[i].getGlobalBounds()))
				{
					block_a[i].setPosition(Settings::position(-1000, 0)); ball->dy = -ball->dy; ++pScore;
				}

			if (Settings::toScreenRect(ball->x, ball->y, 12, 12).intersects(paddle->sprite->getGlobalBounds())) ball->dy = -BALL_SPEED;
		}

		ball->update();

		window->clear();
		window->draw(*s_backg);
		window->draw(*paddle->sprite);
		window->draw(*ball->sprite);

		//Blocks drawing
		for (int i = 0; i < n; i++)
			window->draw(block_a[i]);				

		//Draw text with information about points in upper left corner
		std::ostringstream playerScoreString, gameHS;
		playerScoreString << pScore;
		text->setString("Points: " + playerScoreString.str());
		text->setPosition(Settings::position(0, 0));

		//Draw text with information about points in upper left corner		
		window->draw(*text);
		window->display();

		/*"End screen" start when ball hit the bottom line of window or player get 100 point,
		  include actual score and highscore, highscore rewrite if actual score is higher
		  This information is active while "Space" key is not clicked*/
		if (is_space && ((ball->y > Settings::BASE_HEIGHT) || (pScore == 100)))
		{
			gameHS << get_highscore(pScore);
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && window->isOpen())
			{
				window->clear();
				window->draw(*s_backg);
				text_end->setString("End points: " + playerScoreString.str() + "\nPress space" + "\nHigh Score: " + gameHS.str());
				text_end->setPosition(Settings::position(260, 190));
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