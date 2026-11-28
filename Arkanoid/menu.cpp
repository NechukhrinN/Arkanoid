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

	productInfo = new ProductInfo();
	productInfoLabel = new sf::Text(productInfo->getVersion(), *font, 6);
	productInfoLabel->setFillColor(sf::Color::White);

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
		window->draw(*productInfoLabel);
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

void Menu::reloadResources()
{
	helpTexture->loadFromFile("res/images/help.png");
	aboutTexture->loadFromFile("res/images/about.png");
	menuBackground->loadFromFile("res/images/main_back.jpg");
	font->loadFromFile("res/fonts/arial.TTF");
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

	/*Version info: one fifth of the menu item font size, bottom-right corner*/
	productInfoLabel->setCharacterSize(std::max(1u, fontSize / 5));
	productInfoLabel->setPosition(0.f, 0.f);
	sf::FloatRect infoBounds = productInfoLabel->getLocalBounds();
	float margin = 6.f * s;
	productInfoLabel->setPosition(
		static_cast<float>(Settings::windowWidth) - infoBounds.left - infoBounds.width - margin,
		static_cast<float>(Settings::windowHeight) - infoBounds.top - infoBounds.height - margin);

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
	resolutions = Settings::availableResolutions();

	const float leftX = 60.f;
	const float rightX = 330.f;
	const float boxY = 100.f;
	const float boxWidth = 230.f;
	const float boxHeight = 36.f;
	const float rowHeight = 32.f;
	const float optionsTop = boxY + boxHeight + 4.f;

	int currentResolution = -1;
	for (int i = 0; i < static_cast<int>(resolutions.size()); i++)
	{
		if (resolutions[i].width == Settings::currentResolution.width &&
			resolutions[i].height == Settings::currentResolution.height)
		{
			currentResolution = i;
			break;
		}
	}

	const int currentMode = static_cast<int>(Settings::displayMode);
	const int modeCount = 3;

	int openList = 0; // 0 = closed, 1 = display mode, 2 = resolution
	int highlightedMode = currentMode;
	int highlightedResolution = (currentResolution >= 0) ? currentResolution
		: (resolutions.empty() ? -1 : 0);

	while (window->isOpen())
	{
		int applyMode = -1;
		int applyResolutionIndex = -1;

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
				if (Event->key.code == sf::Keyboard::Escape)
				{
					if (openList != 0)
						openList = 0;
					else
						return;
				}
				else if (Event->key.code == sf::Keyboard::Up)
				{
					if (openList == 1)
					{
						if (highlightedMode > 0)
							highlightedMode--;
						else
							highlightedMode = modeCount - 1;
					}
					else if (openList == 2 && !resolutions.empty())
					{
						if (highlightedResolution > 0)
							highlightedResolution--;
						else
							highlightedResolution = static_cast<int>(resolutions.size()) - 1;
					}
				}
				else if (Event->key.code == sf::Keyboard::Down)
				{
					if (openList == 1)
					{
						if (highlightedMode + 1 < modeCount)
							highlightedMode++;
						else
							highlightedMode = 0;
					}
					else if (openList == 2 && !resolutions.empty())
					{
						if (highlightedResolution + 1 < static_cast<int>(resolutions.size()))
							highlightedResolution++;
						else
							highlightedResolution = 0;
					}
				}
				else if (Event->key.code == sf::Keyboard::Enter)
				{
					if (openList == 1)
						applyMode = highlightedMode;
					else if (openList == 2 && highlightedResolution >= 0)
						applyResolutionIndex = highlightedResolution;
					else if (openList == 0 && !resolutions.empty())
						openList = 2;
				}
			}
			else if (Event->type == sf::Event::MouseMoved && openList != 0)
			{
				sf::Vector2f point = Settings::toVirtual(
					sf::Vector2i(Event->mouseMove.x, Event->mouseMove.y));
				int row = static_cast<int>((point.y - optionsTop) / rowHeight);

				if (point.y >= optionsTop && row >= 0)
				{
					if (openList == 1 &&
						point.x >= leftX && point.x <= leftX + boxWidth &&
						row < modeCount)
					{
						highlightedMode = row;
					}
					else if (openList == 2 &&
							 point.x >= rightX && point.x <= rightX + boxWidth &&
							 row < static_cast<int>(resolutions.size()))
					{
						highlightedResolution = row;
					}
				}
			}
			else if (Event->type == sf::Event::MouseButtonPressed &&
					 Event->mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2f point = Settings::toVirtual(
					sf::Vector2i(Event->mouseButton.x, Event->mouseButton.y));

				bool inModeBox = point.x >= leftX && point.x <= leftX + boxWidth &&
								 point.y >= boxY && point.y <= boxY + boxHeight;
				bool inResolutionBox = point.x >= rightX && point.x <= rightX + boxWidth &&
									   point.y >= boxY && point.y <= boxY + boxHeight;

				if (inModeBox)
				{
					openList = (openList == 1) ? 0 : 1;
					highlightedMode = currentMode;
				}
				else if (inResolutionBox)
				{
					if (!resolutions.empty())
					{
						openList = (openList == 2) ? 0 : 2;
						highlightedResolution = (currentResolution >= 0) ? currentResolution : 0;
					}
				}
				else if (openList != 0 && point.y >= optionsTop)
				{
					int row = static_cast<int>((point.y - optionsTop) / rowHeight);

					if (openList == 1 &&
						point.x >= leftX && point.x <= leftX + boxWidth &&
						row >= 0 && row < modeCount)
					{
						highlightedMode = row;
						applyMode = row;
					}
					else if (openList == 2 &&
							 point.x >= rightX && point.x <= rightX + boxWidth &&
							 row >= 0 && row < static_cast<int>(resolutions.size()))
					{
						highlightedResolution = row;
						applyResolutionIndex = row;
					}
					else
					{
						openList = 0;
					}
				}
				else
				{
					openList = 0;
				}
			}
		}

		if (applyMode >= 0)
		{
			Settings::displayMode = static_cast<Settings::DisplayMode>(applyMode);
			Settings::applyWindowSettings(*window, Settings::WINDOW_TITLE);
			reloadResources();
			layoutMenu();
			return;
		}

		if (applyResolutionIndex >= 0 &&
			applyResolutionIndex < static_cast<int>(resolutions.size()))
		{
			applyResolution(window, resolutions[applyResolutionIndex]);
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
		title.setPosition(Settings::position(leftX, 35));
		window->draw(title);

		sf::Text modeLabel("Display mode", *font,
						   static_cast<unsigned int>(15 * textSize));
		modeLabel.setFillColor(sf::Color(200, 220, 255));
		modeLabel.setPosition(Settings::position(leftX, 70));
		window->draw(modeLabel);

		sf::Text resolutionLabel("Screen resolution", *font,
								 static_cast<unsigned int>(15 * textSize));
		resolutionLabel.setFillColor(sf::Color(200, 220, 255));
		resolutionLabel.setPosition(Settings::position(rightX, 70));
		window->draw(resolutionLabel);

		auto drawCombo = [&](float x, const std::string& text, bool isOpen)
		{
			sf::RectangleShape combo(sf::Vector2f(
				boxWidth * Settings::scaleX, boxHeight * Settings::scaleY));
			combo.setPosition(Settings::position(x, boxY));
			combo.setFillColor(sf::Color(20, 30, 50, 235));
			combo.setOutlineColor(sf::Color(200, 220, 255));
			combo.setOutlineThickness(2.f);
			window->draw(combo);

			sf::Text value(text, *font, static_cast<unsigned int>(18 * textSize));
			value.setFillColor(sf::Color::White);
			value.setPosition(Settings::position(x + 10, boxY + 8));
			window->draw(value);

			sf::Text arrow(isOpen ? "^" : "v", *font,
						   static_cast<unsigned int>(18 * textSize));
			arrow.setFillColor(sf::Color(200, 220, 255));
			arrow.setPosition(Settings::position(x + boxWidth - 24, boxY + 8));
			window->draw(arrow);
		};

		auto drawOptions = [&](float x, const std::vector<std::string>& labels,
							   int highlighted, int current)
		{
			for (int i = 0; i < static_cast<int>(labels.size()); i++)
			{
				float rowY = optionsTop + i * rowHeight;

				sf::RectangleShape option(sf::Vector2f(
					boxWidth * Settings::scaleX,
					(rowHeight - 2) * Settings::scaleY));
				option.setPosition(Settings::position(x, rowY));
				option.setFillColor(i == highlighted
					? sf::Color(60, 110, 180, 240)
					: sf::Color(20, 30, 50, 235));
				option.setOutlineColor(sf::Color(120, 150, 200));
				option.setOutlineThickness(1.f);
				window->draw(option);

				sf::Text item(labels[i], *font,
							  static_cast<unsigned int>(18 * textSize));
				item.setFillColor(i == current ? sf::Color(120, 255, 120)
											   : sf::Color::White);
				item.setPosition(Settings::position(x + 10, rowY + 5));
				window->draw(item);
			}
		};

		drawCombo(leftX, Settings::displayModeName(Settings::displayMode),
				  openList == 1);

		std::string resolutionText;
		if (resolutions.empty())
			resolutionText = "No supported resolutions";
		else if (currentResolution >= 0)
			resolutionText = Settings::resolutionLabel(resolutions[currentResolution]);
		else
			resolutionText = Settings::resolutionName(Settings::currentResolution);

		drawCombo(rightX, resolutionText, openList == 2);

		if (openList == 1)
		{
			std::vector<std::string> labels;
			for (int i = 0; i < modeCount; i++)
				labels.push_back(Settings::displayModeName(
					static_cast<Settings::DisplayMode>(i)));

			drawOptions(leftX, labels, highlightedMode, currentMode);
		}
		else if (openList == 2)
		{
			std::vector<std::string> labels;
			for (const sf::VideoMode& mode : resolutions)
				labels.push_back(Settings::resolutionLabel(mode));

			drawOptions(rightX, labels, highlightedResolution, currentResolution);
		}

		sf::Text hint(openList != 0
			? "Up/Down: select   Enter: apply   Esc: close"
			: "Click a list to change it   Esc: back",
			*font, static_cast<unsigned int>(13 * textSize));
		hint.setFillColor(sf::Color(200, 220, 255));
		hint.setPosition(Settings::position(leftX, 440));
		window->draw(hint);

		window->display();
	}
}

void Menu::applyResolution(sf::RenderWindow* window, const sf::VideoMode& mode)
{
	Settings::currentResolution = sf::VideoMode(mode.width, mode.height);
	Settings::applyWindowSettings(*window, Settings::WINDOW_TITLE);
	reloadResources();
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
	delete(productInfoLabel);
	delete(productInfo);

	delete(font);
};
