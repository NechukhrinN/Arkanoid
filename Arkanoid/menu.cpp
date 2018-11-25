#include "menu.h"

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
	//menuBg.setPosition(345, 0);

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
	bool is_space = false;
	sf::RenderWindow window(sf::VideoMode(640, 480), "Arkanoid!");
	menu(window);
	window.setFramerateLimit(60);
	float CurrentFrame = 0;
	sf::Clock clock_p;
	float dx = 6, dy = 5;
	float x = 309, y = 430;
	int pScore = 0;

	//Loading Font
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
	sf::Image ball_image;
	ball_image.loadFromFile("images/ball.png");
	sf::Image paddle_image;
	paddle_image.loadFromFile("images/paddle_anim.png");
	sf::Image block_image;
	block_image.loadFromFile("images/block.png");
	sf::Image backg_image;
	backg_image.loadFromFile("images/background.jpg");

	//Loading textures from images
	sf::Texture map;
	map.loadFromImage(map_image);
	sf::Texture ball;
	ball.loadFromImage(ball_image);
	sf::Texture paddle;
	paddle.loadFromImage(paddle_image);
	sf::Texture block;
	block.loadFromImage(block_image);
	sf::Texture backg;
	backg.loadFromImage(backg_image);

	//Loading sprites from textures
	sf::Sprite s_map;
	s_map.setTexture(map);
	sf::Sprite s_ball;
	s_ball.setTexture(ball);
	sf::Sprite s_paddle;
	s_paddle.setTexture(paddle);
	sf::Sprite s_block;
	s_block.setTexture(block);
	sf::Sprite s_backg;
	s_backg.setTexture(backg);

	s_paddle.setPosition(270, 450);
	s_ball.setPosition(309, 430);
	sf::Sprite block_a[1000];

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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) return true;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) return false;

		window.clear();
		window.draw(s_backg);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			//window.close(); 
			menu(window);
		}

		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) s_paddle.move(8, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) s_paddle.move(-8, 0);

		

		

		float time = clock_p.getElapsedTime().asMicroseconds();
		clock_p.restart();
		time = time / 800;

		//Paddle animation
		CurrentFrame += 0.008*time;
		if (CurrentFrame > 14) CurrentFrame -= 14;
		s_paddle.setTextureRect(sf::IntRect(0, 9 * int(CurrentFrame), 90, 9));
		window.draw(s_paddle);

		//Blocks draw
		for (int i = 0; i < n; i++)
			window.draw(block_a[i]);

		//Draw text with information about points
		std::ostringstream playerScoreString, gameTimeString;
		playerScoreString << pScore;
		//gameTimeString << gameTime;
		text.setString("Points: " + playerScoreString.str());
		text.setPosition(0, 0);
		window.draw(s_ball);
		window.draw(text);
		window.display();

		while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (is_space == false))
		{
			dx = 0;
			dy = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			dx = 6;
			dy = -5;
			is_space = true;
		}
		x += dx;
		for (int i = 0; i < n; i++)
			if (sf::FloatRect(x + 3, y + 3, 6, 6).intersects(block_a[i].getGlobalBounds()))
			{
				block_a[i].setPosition(-100, 0); dx = -dx; ++pScore;
			}

		y += dy;
		for (int i = 0; i < n; i++)
			if (sf::FloatRect(x + 3, y + 3, 6, 6).intersects(block_a[i].getGlobalBounds()))
			{
				block_a[i].setPosition(-100, 0); dy = -dy; ++pScore;
			}

		if (x < 0 || x>640)  dx = -dx;
		if (y < 0)  dy = -dy;
		if (y > 480)
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
		if (sf::FloatRect(x, y, 12, 12).intersects(s_paddle.getGlobalBounds())) dy = -(rand() % 5 + 2);
		s_ball.setPosition(x, y);

		
	}

}

void gameRunning()
{
	if (startGame()) gameRunning();
}

