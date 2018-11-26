#include "menu.h"
#include "paddle.h"
#include "ball.h"

void menu(sf::RenderWindow & window) {
	sf::Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/111.png");
	menuTexture2.loadFromFile("images/222.png");
	menuTexture3.loadFromFile("images/333.png");
	aboutTexture.loadFromFile("images/about.png");
	menuBackground.loadFromFile("images/main_back.jpg");
	sf::Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), about(aboutTexture), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	window.draw(menuBg);
	menu1.setPosition(100, 30);
	menu2.setPosition(100, 90);
	menu3.setPosition(100, 150);

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
		menuNum = 0;
		window.clear(sf::Color(129, 181, 221));

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

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.draw(about);	window.display(); while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(menu3);

		window.display();
	}
}


int startGame()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid by Nikita Nechukhrin");
	menu(window);
	window.setFramerateLimit(60);
	float CurrentFrame = 0;
	sf::Clock clock_p;

	bool is_space = false;
	int pScore = 0;

	//Loading Fonts
	sf::Font font;
	font.loadFromFile("fonts/arial.ttf");
	sf::Text text("", font, 20);
	text.setFillColor(sf::Color::White);
	sf::Text text_begin("", font, 20);
	text_begin.setFillColor(sf::Color::Black);
	sf::Text text_end("", font, 20);
	text_end.setFillColor(sf::Color::Red);

	//Loading Images
	sf::Image map_image;
	map_image.loadFromFile("images/map.png");
	sf::Image block_image;
	block_image.loadFromFile("images/block.png");
	sf::Image backg_image;
	backg_image.loadFromFile("images/background.jpg");

	//Loading textures from images
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Texture block;
	block.loadFromImage(block_image);
	sf::Texture backg;
	backg.loadFromImage(backg_image);

	//Loading sprites from textures
	sf::Sprite s_map;
	s_map.setTexture(map);
	sf::Sprite s_block;
	s_block.setTexture(block);
	sf::Sprite s_backg;
	s_backg.setTexture(backg);

	sf::Sprite block_a[1000];
	Ball ball("ball.png", 309,435, 12, 12);
	Paddle paddle("paddle_anim.png", 270, 450, 90, 9);
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
		sf::Event e;
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				window.close();
		}

		float time = clock_p.getElapsedTime().asMicroseconds();
		clock_p.restart();
		time = time / 800;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return false;

			
		window.clear();
		window.draw(s_backg);
		paddle.update(time);
		window.draw(paddle.sprite);
		ball.update();
		window.draw(ball.sprite);
		
		//Blocks draw
		for (int i = 0; i < n; i++)
			window.draw(block_a[i]);

		//Draw text with information about points
		std::ostringstream playerScoreString, gameTimeString;
		playerScoreString << pScore;
		text.setString("Points: " + playerScoreString.str());
		text.setPosition(0, 0);
		
		window.draw(text);
		window.display();

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
		
		ball.x += ball.dx;
	
		for (int i = 0; i < n; i++)
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

		
		//Ending screen
		if (ball.y > 480)
		{
			while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				window.clear();
				window.draw(s_backg);
				text_end.setString("End points: " + playerScoreString.str() + "\nPress space");
				text_end.setPosition(260, 190);
				window.draw(text_end);
				window.display();
			}
			return -1;
		}
		
		if (sf::FloatRect(ball.x, ball.y, 12, 12).intersects(paddle.sprite.getGlobalBounds())) ball.dy = -5;
				
	}

}

void gameRunning()
{
	if (startGame()) gameRunning();
}

