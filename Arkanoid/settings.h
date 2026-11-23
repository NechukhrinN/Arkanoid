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

	inline std::vector<sf::VideoMode> availableResolutions()
	{
		std::vector<sf::VideoMode> all = sf::VideoMode::getFullscreenModes();
		all.push_back(sf::VideoMode::getDesktopMode());

		std::vector<sf::VideoMode> modes;
		for (const sf::VideoMode& mode : all)
		{
			if (mode.width < 640 || mode.height < 480)
				continue;

			bool duplicate = false;
			for (const sf::VideoMode& existing : modes)
			{
				if (existing.width == mode.width && existing.height == mode.height)
				{
					duplicate = true;
					break;
				}
			}

			if (!duplicate)
				modes.push_back(mode);
		}

		std::sort(modes.begin(), modes.end(),
			[](const sf::VideoMode& a, const sf::VideoMode& b)
			{
				if (a.width != b.width)
					return a.width < b.width;
				return a.height < b.height;
			});

		return modes;
	}

	inline std::string resolutionName(const sf::VideoMode& mode)
	{
		return std::to_string(mode.width) + " x " + std::to_string(mode.height);
	}
}

#endif
