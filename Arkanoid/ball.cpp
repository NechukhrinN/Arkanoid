#include "ball.h"

/*Constructor of class Ball, get starter information about object, include acceleration and sprite*/
Ball::Ball(const sf::String& F, const float& X, const float& Y, const float& W, const float& H)
{
	File = new sf::String(F);
	image = new sf::Image();
	texture = new sf::Texture();
	sprite = new sf::Sprite();

	dx = 5; dy = -5;	
	w = W; h = H;
	image->loadFromFile("res/images/" + *File);
	texture->loadFromImage(*image);
	sprite->setTexture(*texture);
	x = X; y = Y;
	sprite->setTextureRect(sf::IntRect(0, 0, w, h));
}

Ball::~Ball() 
{
	delete(File);
	delete(image);
	delete(texture);
	delete(sprite);
}
/*Update method sets ball position and ball's collision with wall*/
void Ball::update()
{	
	if (x < 0 || x > 640)  dx = -dx;
	if (y < 0)  dy = -dy;
	sprite->setPosition(x, y);
}

void Ball::update(const float& time)
{
	if (x < 0 || x > 640)  dx = -dx;
	if (y < 0)  dy = -dy;
	sprite->setPosition(x, y);
}


/*float Ball::getballcoordinateX()
{
	return x;
}

float Ball::getballcoordinateY()
{
	return y;
}*/