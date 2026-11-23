#include "menu.h"
#include "settings.h"


Menu::Menu(sf::RenderWindow* window)
{
	game = nullptr;
	Event = new sf::Event;

	Settings::updateLayout(*window);
	Settings::applyView(*window);

	/*Loading textures of the menu background and info screens*/
	helpTexture = new sf::Texture;
	highscoreTexture = new sf::Texture;
	aboutTexture = new sf::Texture;
	menuBackground = new sf::Texture;

	helpTexture->loadFromFile("res/images/help.png");
	aboutTexture->loadFromFile("res/images/about.png");
	menuBackground->loadFromFile("res/images/main_back.jpg");

	help = new sf::Sprite(*helpTexture);
	about = new sf::Sprite(*aboutTexture);
	menuBg = new sf::Sprite(*menuBackground);

	font = new sf::Font;
	font->loadFromFile("res/fonts/arial.TTF");

	newGameLabel = new sf::Text("New Game", *font, 30);
	newGameLabel->setFillColor(sf::Color::White);
	helpLabel = new sf::Text("Help", *font, 30);
	helpLabel->setFillColor(sf::Color::White);
	aboutLabel = new sf::Text("About", *font, 30);
	aboutLabel->setFillColor(sf::Color::White);
	settingsLabel = new sf::Text("Settings", *font, 30);
	settingsLabel->setFillColor(sf::Color::White);
	exitLabel = new sf::Text("Exit", *font, 30);
	exitLabel->setFillColor(sf::Color::White);

	resolutions = Settings::availableResolutions();

	layoutMenu();

	isMenu = 1;
	menuNum = 0;

	while (isMenu && window->isOpen())
	{
		bool clicked = false;

		while (window->pollEvent(*Event))
		{
			if (Event->type == sf::Event::Closed)
			{
				window->close();
				isMenu = false;
			}
			else if (Event->type == sf::Event::Resized &&
					 Event->size.width > 0 && Event->size.height > 0)
			{
				Settings::updateLayout(Event->size.width, Event->size.height);
				Settings::applyView(*window);
				layoutMenu();
			}
			else if (Event->type == sf::Event::MouseButtonPressed &&
					 Event->mouseButton.button == sf::Mouse::Left)
			{
				clicked = true;
			}
		}

		newGameLabel->setFillColor(sf::Color::White);
		helpLabel->setFillColor(sf::Color::White);
		aboutLabel->setFillColor(sf::Color::White);
		settingsLabel->setFillColor(sf::Color::White);
		exitLabel->setFillColor(sf::Color::White);
		menuNum = 0;

		sf::Vector2f mouse = Settings::toVirtual(sf::Mouse::getPosition(*window));

		/*Activation of the backlight when you hover the mouse*/
		if (sf::FloatRect(100, 30, 300, 50).contains(mouse)) {
			newGameLabel->setFillColor(sf::Color::Blue);
			menuNum = 1;
		}
		if (sf::FloatRect(100, 90, 300, 50).contains(mouse)) {
			helpLabel->setFillColor(sf::Color::Blue);
			menuNum = 2;
		}
		if (sf::FloatRect(100, 150, 300, 50).contains(mouse)) {
			aboutLabel->setFillColor(sf::Color::Blue);
			menuNum = 3;
		}
		if (sf::FloatRect(100, 210, 300, 50).contains(mouse)) {
			settingsLabel->setFillColor(sf::Color::Blue);
			menuNum = 4;
		}
		if (sf::FloatRect(100, 270, 300, 50).contains(mouse)) {
			exitLabel->setFillColor(sf::Color::Blue);
			menuNum = 5;
		}

		window->clear(sf::Color(129, 181, 221));
		window->draw(*menuBg);
		window->draw(*newGameLabel);
		window->draw(*helpLabel);
		window->draw(*aboutLabel);
		window->draw(*settingsLabel);
		window->draw(*exitLabel);
		window->display();

		/*Click processing*/
		if (clicked)
		{
			if (menuNum == 1)
			{
				game = new MainGame();
				game->StartGame(window);
				delete(game);
				game = nullptr;
			}
			else if (menuNum == 2)
			{
				showInfo(window, help);
			}
			else if (menuNum == 3)
			{
				showInfo(window, about);
			}
			else if (menuNum == 4)
			{
				showSettings(window);
			}
			else if (menuNum == 5)
			{
				window->close();
				isMenu = false;
			}
		}
	}
}

void Menu::layoutMenu()
{
	const float s = Settings::textScale();

	/*The background fills the whole window; the rest keeps the 4:3 layout*/
	menuBg->setPosition(0.f, 0.f);
	menuBg->setScale(Settings::scaleX, Settings::scaleY);

	const unsigned int fontSize = static_cast<unsigned int>(30 * s);

	newGameLabel->setCharacterSize(fontSize);
	newGameLabel->setPosition(Settings::position(100, 30));
	helpLabel->setCharacterSize(fontSize);
	helpLabel->setPosition(Settings::position(100, 90));
	aboutLabel->setCharacterSize(fontSize);
	aboutLabel->setPosition(Settings::position(100, 150));
	settingsLabel->setCharacterSize(fontSize);
	settingsLabel->setPosition(Settings::position(100, 210));
	exitLabel->setCharacterSize(fontSize);
	exitLabel->setPosition(Settings::position(100, 270));

	help->setScale(Settings::scaleX, Settings::scaleY);
	help->setPosition(Settings::position(0, 0));
	about->setScale(Settings::scaleX, Settings::scaleY);
	about->setPosition(Settings::position(0, 0));
}

void Menu::showInfo(sf::RenderWindow* window, sf::Sprite* screen)
{
	while (window->isOpen())
	{
		while (window->pollEvent(*Event))
		{
			if (Event->type == sf::Event::Closed)
			{
				window->close();
				isMenu = false;
				return;
			}
			if (Event->type == sf::Event::Resized &&
				Event->size.width > 0 && Event->size.height > 0)
			{
				Settings::updateLayout(Event->size.width, Event->size.height);
				Settings::applyView(*window);
				layoutMenu();
			}
			if (Event->type == sf::Event::KeyPressed &&
				Event->key.code == sf::Keyboard::Escape)
			{
				return;
			}
		}

		window->clear(sf::Color::Black);
		window->draw(*menuBg);
		window->draw(*screen);
		window->display();
	}
}

void Menu::showSettings(sf::RenderWindow* window)
{
	const float listX = 100.f;
	const float listTop = 105.f;
	const float rowHeight = 24.f;
	const int visibleRows = 13;

	const int lastRow = (static_cast<int>(resolutions.size()) > visibleRows)
		? static_cast<int>(resolutions.size()) - visibleRows : 0;

	int selected = 0;
	for (int i = 0; i < static_cast<int>(resolutions.size()); i++)
	{
		if (resolutions[i].width == Settings::windowWidth &&
			resolutions[i].height == Settings::windowHeight)
		{
			selected = i;
			break;
		}
	}

	int firstVisible = 0;
	if (selected >= visibleRows)
		firstVisible = selected - visibleRows + 1;

	if (resolutions.empty())
		return;

	while (window->isOpen())
	{
		int applyIndex = -1;

		while (window->pollEvent(*Event))
		{
			if (Event->type == sf::Event::Closed)
			{
				window->close();
				isMenu = false;
				return;
			}
			else if (Event->type == sf::Event::Resized &&
					 Event->size.width > 0 && Event->size.height > 0)
			{
				Settings::updateLayout(Event->size.width, Event->size.height);
				Settings::applyView(*window);
				layoutMenu();
			}
			else if (Event->type == sf::Event::KeyPressed)
			{
				if (Event->key.code == sf::Keyboard::Up && selected > 0)
					selected--;
				else if (Event->key.code == sf::Keyboard::Down &&
						 selected + 1 < static_cast<int>(resolutions.size()))
					selected++;
				else if (Event->key.code == sf::Keyboard::Enter)
					applyIndex = selected;
				else if (Event->key.code == sf::Keyboard::Escape)
					return;
			}
			else if (Event->type == sf::Event::MouseWheelScrolled &&
					 Event->mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			{
				firstVisible -= static_cast<int>(Event->mouseWheelScroll.delta);
				if (firstVisible < 0)
					firstVisible = 0;
				if (firstVisible > lastRow)
					firstVisible = lastRow;

				if (selected < firstVisible)
					selected = firstVisible;
				if (selected >= firstVisible + visibleRows)
					selected = firstVisible + visibleRows - 1;
			}
			else if (Event->type == sf::Event::MouseMoved)
			{
				sf::Vector2f point = Settings::toVirtual(
					sf::Vector2i(Event->mouseMove.x, Event->mouseMove.y));
				int row = static_cast<int>((point.y - listTop) / rowHeight);

				if (point.x >= listX - 10 && point.x <= listX + 440 &&
					row >= 0 && row < visibleRows &&
					firstVisible + row < static_cast<int>(resolutions.size()))
				{
					selected = firstVisible + row;
				}
			}
			else if (Event->type == sf::Event::MouseButtonPressed &&
					 Event->mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f point = Settings::toVirtual(
					sf::Vector2i(Event->mouseButton.x, Event->mouseButton.y));
				int row = static_cast<int>((point.y - listTop) / rowHeight);

				if (point.x >= listX - 10 && point.x <= listX + 440 &&
					row >= 0 && row < visibleRows &&
					firstVisible + row < static_cast<int>(resolutions.size()))
				{
					selected = firstVisible + row;
					applyIndex = selected;
				}
			}
		}

		if (selected < firstVisible)
			firstVisible = selected;
		if (selected >= firstVisible + visibleRows)
			firstVisible = selected - visibleRows + 1;
		if (firstVisible < 0)
			firstVisible = 0;
		if (firstVisible > lastRow)
			firstVisible = lastRow;

		if (applyIndex >= 0 && applyIndex < static_cast<int>(resolutions.size()))
		{
			applyResolution(window, resolutions[applyIndex]);
			return;
		}

		const float textSize = Settings::textScale();

		window->clear(sf::Color::Black);
		window->draw(*menuBg);

		sf::RectangleShape shade(sf::Vector2f(
			static_cast<float>(Settings::windowWidth),
			static_cast<float>(Settings::windowHeight)));
		shade.setFillColor(sf::Color(0, 0, 0, 160));
		window->draw(shade);

		sf::Text title("Settings", *font, static_cast<unsigned int>(28 * textSize));
		title.setFillColor(sf::Color::White);
		title.setPosition(Settings::position(listX, 35));
		window->draw(title);

		sf::Text subtitle("Choose window resolution", *font,
						  static_cast<unsigned int>(15 * textSize));
		subtitle.setFillColor(sf::Color(200, 220, 255));
		subtitle.setPosition(Settings::position(listX, 75));
		window->draw(subtitle);

		for (int row = 0; row < visibleRows; row++)
		{
			int index = firstVisible + row;
			if (index >= static_cast<int>(resolutions.size()))
				break;

			if (index == selected)
			{
				sf::RectangleShape highlight(sf::Vector2f(
					440 * Settings::scaleX, (rowHeight - 2) * Settings::scaleY));
				highlight.setPosition(Settings::position(
					listX - 10, listTop + row * rowHeight - 1));
				highlight.setFillColor(sf::Color(60, 110, 180, 230));
				window->draw(highlight);
			}

			bool current = (resolutions[index].width == Settings::windowWidth &&
							resolutions[index].height == Settings::windowHeight);

			std::string label = Settings::resolutionName(resolutions[index]);
			if (current)
				label += "   (current)";

			sf::Text item(label, *font, static_cast<unsigned int>(18 * textSize));
			item.setFillColor(current ? sf::Color(120, 255, 120) : sf::Color::White);
			item.setPosition(Settings::position(
				listX, listTop + row * rowHeight));
			window->draw(item);
		}

		sf::Text hint("Up/Down: select   Enter: apply   Esc: back   Wheel: scroll",
					  *font, static_cast<unsigned int>(13 * textSize));
		hint.setFillColor(sf::Color(200, 220, 255));
		hint.setPosition(Settings::position(listX, 440));
		window->draw(hint);

		std::string counter = std::to_string(firstVisible + 1) + "-" +
			std::to_string(std::min(firstVisible + visibleRows,
									static_cast<int>(resolutions.size()))) +
			" of " + std::to_string(resolutions.size());
		sf::Text counterText(counter, *font, static_cast<unsigned int>(13 * textSize));
		counterText.setFillColor(sf::Color(200, 220, 255));
		counterText.setPosition(Settings::position(470, 75));
		window->draw(counterText);

		window->display();
	}
}

void Menu::applyResolution(sf::RenderWindow* window, const sf::VideoMode& mode)
{
	window->setSize(sf::Vector2u(mode.width, mode.height));

	sf::Vector2u actual = window->getSize();
	Settings::updateLayout(actual.x, actual.y);
	Settings::applyView(*window);

	sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
	int x = (static_cast<int>(desktop.width) - static_cast<int>(actual.x)) / 2;
	int y = (static_cast<int>(desktop.height) - static_cast<int>(actual.y)) / 2;
	window->setPosition(sf::Vector2i(std::max(0, x), std::max(0, y)));

	layoutMenu();
}

//Reverce to restart game
//void gameRunning(sf::RenderWindow& window)
//{
//	if (startGame(window)) gameRunning(window);
//}

Menu::~Menu()
{		
	delete(game);
	delete(Event);

	delete(helpTexture);
	delete(highscoreTexture);
	delete(aboutTexture);
	delete(menuBackground);

	delete(help);
	delete(about);
	delete(menuBg);

	delete(newGameLabel);
	delete(helpLabel);
	delete(aboutLabel);
	delete(settingsLabel);
	delete(exitLabel);

	delete(font);
};
