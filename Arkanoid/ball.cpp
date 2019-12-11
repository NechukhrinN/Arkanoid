#include "ball.h"

/*Constructor of class Ball, get starter information about object, include acceleration and sprite*/
Ball::Ball(sf::String F, float X, float Y, float W, float H)
{
	dx = 5; dy = -5;
	File = F;
	w = W; h = H;
	image.loadFromFile("res/images/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X; y = Y;
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

Ball::~Ball() {}
/*Update method sets ball position and ball's collision with wall*/
void Ball::update()
{	
	if (x < 0 || x > 640)  dx = -dx;
	if (y < 0)  dy = -dy;
	sprite.setPosition(x, y);
}


/*float Ball::getballcoordinateX()
{
	return x;
}

float Ball::getballcoordinateY()
{
	return y;
}*/