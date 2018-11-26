#include "menu.h"
#include "paddle.h"
#include "ball.h"


/*Main menu*/
void menu(sf::RenderWindow & window) {

	/*Loading bottom's sprites and set bottom's position*/
	sf::Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, helpTexture, highscoreTexture, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("res/images/ngame.png");
	menuTexture2.loadFromFile("res/images/help_m.png");
	menuTexture3.loadFromFile("res/images/about_m.png");
	menuTexture4.loadFromFile("res/images/exit.png");
	helpTexture.loadFromFile("res/images/help.png");
	aboutTexture.loadFromFile("res/images/about.png");
	menuBackground.loadFromFile("res/images/main_back.jpg");
	sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menu4(menuTexture4), help(helpTexture), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	window.draw(menuBg);
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);
	menu4.setPosition(100, 210);

	while (isMenu)
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		menu1.setColor(sf::Color::White);
		menu2.setColor(sf::Color::White);
		menu3.setColor(sf::Color::White);
		menu4.setColor(sf::Color::White);
		menuNum = 0;
		window.clear(sf::Color(129, 181, 221));

		/*Activation of the backlight when you hover the mouse*/
		if (sf::IntRect(100, 30, 300, 50).contains(sf::Mouse::getPosition(window))) {
			menu1.setColor(sf::Color::Blue);
			menuNum = 1;
		}
		if (sf::IntRect(100, 90, 300, 50).contains(sf::Mouse::getPosition(window))) {
			menu2.setColor(sf::Color::Blue);
			menuNum = 2;
		}
		if (sf::IntRect(100, 150, 300, 50).contains(sf::Mouse::getPosition(window))) {
			menu3.setColor(sf::Color::Blue);
			menuNum = 3;
		}
		if (sf::IntRect(100, 210, 300, 50).contains(sf::Mouse::getPosition(window))) {
			menu4.setColor(sf::Color::Blue);
			menuNum = 4;
		}

		/*Click processing*/
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.draw(help);	window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
			if (menuNum == 3) { window.draw(about);	window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
			if (menuNum == 4) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);
		window.draw(menu4);

		window.display();
	}
}


int startGame()
{
	/*Game window*/
	sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid by Nikita Nechukhrin");
	menu(window);
	window.setFramerateLimit(60);
	int pScore = 0;
	float CurrentFrame = 0;
	sf::Clock clock_p;

	bool is_space = false;
	

	//Loading Fonts fot point counter end endgame message
	sf::Font font;
	font.loadFromFile("res/fonts/arial.ttf");
	sf::Text text("", font, 20);
	text.setFillColor(sf::Color::White);
	sf::Text text_begin("", font, 20);
	text_begin.setFillColor(sf::Color::Black);
	sf::Text text_end("", font, 20);
	text_end.setFillColor(sf::Color::Red);

	//Loading Images of blocks and backgound
	sf::Image block_image;
	block_image.loadFromFile("res/images/block.png");
	sf::Image backg_image;
	backg_image.loadFromFile("res/images/background.jpg");

	//Loading textures of blocks and backgound from images
	sf::Texture block;
	block.loadFromImage(block_image);
	sf::Texture backg;
	backg.loadFromImage(backg_image);

	//Loading sprites of blocks and backgound from textures
	sf::Sprite s_block;
	s_block.setTexture(block);
	sf::Sprite s_backg;
	s_backg.setTexture(backg);

	/*Making array with information of position of blocks*/
	sf::Sprite block_a[100]; 
	int n = 0;
	for (int i = 1; i <= 10; i++)
		for (int j = 1; j <= 10; j++)
		{
			block_a[n].setTexture(block);
			block_a[n].setPosition(i * 55, j * 25);
			n++;
		}
	
	/*Creating Ball/Paddle objects with starter information about position and sprites location*/
	Ball ball("ball.png", 309,435, 12, 12);
	Paddle paddle("paddle_anim.png", 270, 450, 90, 9);
	

	while (window.isOpen())
	{
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		/*Timer for animation and object's movement*/
		float time = static_cast<float>(clock_p.getElapsedTime().asMicroseconds());
		clock_p.restart();
		time = time / 800;

		/*Keys for restart and close game, active in game window since game start*/
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return false;

		window.clear();
		window.draw(s_backg);
		paddle.update(time);
		window.draw(paddle.sprite);
		ball.update();
		window.draw(ball.sprite);
		
		//Blocks drawing
		for (int i = 0; i < n; i++)
			window.draw(block_a[i]);

		//Draw text with information about points in upper left corner
		std::ostringstream playerScoreString, gameHS;
		playerScoreString << pScore;
		text.setString("Points: " + playerScoreString.str());
		text.setPosition(0, 0);
		
		window.draw(text);
		window.display();

		/*Game doesn't start while player don't press "Space" bottom*/
		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (is_space == false))
		{			
			ball.dx = 0;
			ball.dy = 0;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			ball.dx = 5;
			ball.dy = -5;
			is_space = true;
		}
		
		/*Ball's movement realization and ball's collision with blocks and puddle*/
		ball.x += ball.dx;
	
		for (int i = 0; i < n; i++)
			/*The sprite of ball is square, to get collision with circle I need to change the border of the sprite,
			  so that the sprite of the ball is superimposed on the sprite of the block*/
			if (sf::FloatRect(ball.x + 3, ball.y + 3, 6, 6).intersects(block_a[i].getGlobalBounds()))
			{
				block_a[i].setPosition(-100, 0); ball.dx = -ball.dx; ++pScore;
			}

		ball.y += ball.dy;

		for (int i = 0; i < n; i++)
			if (sf::FloatRect(ball.x + 3, ball.y + 3, 6, 6).intersects(block_a[i].getGlobalBounds()))
			{
				block_a[i].setPosition(-100, 0); ball.dy = -ball.dy; ++pScore;
			}

		if (sf::FloatRect(ball.x, ball.y, 12, 12).intersects(paddle.sprite.getGlobalBounds())) ball.dy = -5;

		/*"End screen" start when ball hit the bottom line of window or player get 100 point,
		  include actual score and highscore, highscore rewrite if actual score is higher
		  This information is active while "Space" key is not clicked*/
		if ((ball.y > 480) || (pScore == 100))
		{
			gameHS << get_highscore(pScore);
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				window.clear();
				window.draw(s_backg);
				text_end.setString("End points: " + playerScoreString.str() + "\nPress space" + "\nHigh Score: " + gameHS.str());
				text_end.setPosition(260, 190);				
				window.draw(text_end);
				window.display();
			}
			
			return -1;
		}
				
	}

}
//Reverce to restart game
void gameRunning()
{
	if (startGame()) gameRunning();
}

