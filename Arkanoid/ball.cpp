#include "ball.h"

Ball::Ball(sf::String F, float X, float Y, float W, float H)
{
	dx = 5; dy = -5;
	File = F;
	w = W; h = H;
	image.loadFromFile("images/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X; y = Y;
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

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