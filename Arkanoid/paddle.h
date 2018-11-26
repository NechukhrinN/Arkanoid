#ifndef  PADDLE
#define PADDLE
#include <SFML\Graphics.hpp>

class Paddle
{
private: float x, y;
public:
	bool life;
	int dir, pScore, health;
	float w, h, dx, speed, CurrentFrame = 0;;
	sf::String File;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	Paddle(sf::String F, float X, float Y, float W, float H);
	void interactionWithMap();
	void update(float time);
	float getpaddlecoordinateX();
	float getpaddlecoordinateY();
};

#endif
