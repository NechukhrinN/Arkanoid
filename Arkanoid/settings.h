#ifndef  SETTINGS
#define SETTINGS
#include <SFML\Graphics.hpp>
#include <algorithm>
#include <string>
#include <vector>

/*The whole game is laid out in a virtual 640x480 space.  These helpers stretch
  that space to the actual window resolution, so the game fills the window and
  every position/size stays correct when another resolution is selected.*/
namespace Settings
{
	const float BASE_WIDTH = 640.f;
	const float BASE_HEIGHT = 480.f;

	enum class DisplayMode
	{
		Fullscreen = 0,
		Windowed = 1,
		Borderless = 2
	};

	inline const char* const WINDOW_TITLE = "Arkanoid by Nikita Nechukhrin";
	inline DisplayMode displayMode = DisplayMode::Fullscreen;
	inline sf::VideoMode currentResolution(640, 480);

	inline unsigned int windowWidth = 640;
	inline unsigned int windowHeight = 480;
	inline float scaleX = 1.f;
	inline float scaleY = 1.f;

	inline void updateLayout(unsigned int width, unsigned int height)
	{
		windowWidth = (width > 0) ? width : static_cast<unsigned int>(BASE_WIDTH);
		windowHeight = (height > 0) ? height : static_cast<unsigned int>(BASE_HEIGHT);
		scaleX = windowWidth / BASE_WIDTH;
		scaleY = windowHeight / BASE_HEIGHT;
	}

	inline void updateLayout(const sf::RenderWindow& window)
	{
		sf::Vector2u size = window.getSize();
		updateLayout(size.x, size.y);
	}

	//Keep the render view in pixel coordinates after a window resize.
	inline void applyView(sf::RenderWindow& window)
	{
		window.setView(sf::View(sf::FloatRect(0.f, 0.f,
			static_cast<float>(windowWidth), static_cast<float>(windowHeight))));
	}

	//Text should keep its aspect ratio, so use the smaller factor for fonts.
	inline float textScale() { return std::min(scaleX, scaleY); }

	inline float toScreenX(float value) { return value * scaleX; }
	inline float toScreenY(float value) { return value * scaleY; }

	inline sf::Vector2f position(float x, float y)
	{
		return sf::Vector2f(toScreenX(x), toScreenY(y));
	}

	inline sf::Vector2f position(const sf::Vector2f& point)
	{
		return position(point.x, point.y);
	}

	inline sf::Vector2f toVirtual(const sf::Vector2i& point)
	{
		return sf::Vector2f(point.x / scaleX, point.y / scaleY);
	}

	inline sf::FloatRect toScreenRect(float x, float y, float width, float height)
	{
		return sf::FloatRect(toScreenX(x), toScreenY(y),
							 width * scaleX, height * scaleY);
	}

	inline std::string resolutionName(const sf::VideoMode& mode)
	{
		return std::to_string(mode.width) + " x " + std::to_string(mode.height);
	}

	inline std::string resolutionLabel(const sf::VideoMode& mode)
	{
		if (mode.width == 1280 && mode.height == 720)
			return resolutionName(mode) + " (720p)";
		if (mode.width == 1920 && mode.height == 1080)
			return resolutionName(mode) + " (1080p)";
		if (mode.width == 2560 && mode.height == 1440)
			return resolutionName(mode) + " (2K)";
		if (mode.width == 3840 && mode.height == 2160)
			return resolutionName(mode) + " (4K)";
		return resolutionName(mode);
	}

	inline std::string displayModeName(DisplayMode mode)
	{
		switch (mode)
		{
			case DisplayMode::Fullscreen: return "Fullscreen";
			case DisplayMode::Windowed: return "Windowed";
			case DisplayMode::Borderless: return "Borderless windowed";
		}
		return "Windowed";
	}

	inline std::vector<sf::VideoMode> availableResolutions()
	{
		const sf::VideoMode targets[] = {
			sf::VideoMode(1280, 720),
			sf::VideoMode(1920, 1080),
			sf::VideoMode(2560, 1440),
			sf::VideoMode(3840, 2160)
		};

		std::vector<sf::VideoMode> supported = sf::VideoMode::getFullscreenModes();
		supported.push_back(sf::VideoMode::getDesktopMode());

		std::vector<sf::VideoMode> modes;
		for (const sf::VideoMode& target : targets)
		{
			for (const sf::VideoMode& mode : supported)
			{
				if (mode.width == target.width && mode.height == target.height)
				{
					modes.push_back(target);
					break;
				}
			}
		}

		return modes;
	}

	inline sf::VideoMode highestSupportedResolution()
	{
		std::vector<sf::VideoMode> modes = availableResolutions();
		if (!modes.empty())
			return modes.back();

		sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
		return sf::VideoMode(desktop.width, desktop.height);
	}

	inline void applyWindowSettings(sf::RenderWindow& window, const std::string& title)
	{
		sf::Uint32 style = sf::Style::Titlebar | sf::Style::Close;
		if (displayMode == DisplayMode::Fullscreen)
			style = sf::Style::Fullscreen;
		else if (displayMode == DisplayMode::Borderless)
			style = sf::Style::None;

		window.create(currentResolution, title, style);
		window.setFramerateLimit(60);

		if (displayMode != DisplayMode::Fullscreen)
		{
			sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
			int x = (static_cast<int>(desktop.width) -
					 static_cast<int>(currentResolution.width)) / 2;
			int y = (static_cast<int>(desktop.height) -
					 static_cast<int>(currentResolution.height)) / 2;
			window.setPosition(sf::Vector2i(std::max(0, x), std::max(0, y)));
		}

		updateLayout(window);
		applyView(window);
	}
}

#endif
