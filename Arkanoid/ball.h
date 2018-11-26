#ifndef  BALL
#define BALL
#include <SFML\Graphics.hpp>

class Ball
{ 
public:
	float w, h, dx, dy;
	float x, y;
	sf::String File;
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;

	Ball(sf::String F, float X, float Y, float W, float H);
	void update();
	float getballcoordinateX();
	float getballcoordinateY();
};

#endif