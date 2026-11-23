#include "paddle.h"
#include "settings.h"

namespace
{
	//Virtual pixels per second, independent of the frame rate.
	const float PADDLE_SPEED = 625.0f;
	const float PADDLE_ANIMATION_SPEED = 10.0f;
}

/*Constructor of class Paddle, get starter information about object, include acceleration and sprite*/
Paddle::Paddle(const sf::String& F, const float& X, const float& Y, const float& W, const float& H)
{
	File = new sf::String(F);
	image = new sf::Image();
	texture = new sf::Texture();
	sprite = new sf::Sprite();

	dx = 0; speed = 0;	
	w = W; h = H;
	CurrentFrame = 0;
	image->loadFromFile("res/images/" + *File);
	texture->loadFromImage(*image);
	sprite->setTexture(*texture);
	sprite->setScale(Settings::scaleX, Settings::scaleY);
	x = X; y = Y;
	sprite->setTextureRect(sf::IntRect(0, 0, static_cast<int>(w), static_cast<int>(h)));
	sprite->setPosition(Settings::position(x, y));
}

/*Method update: realizes object movement*/
void Paddle::update(const float& time)
{
	switch (dir)
	{
		case 0: dx = speed; break;
		case 1: dx = -speed; break;
		default: dx = 0; break;
	}
	x += dx * time;
	speed = 0;
	sprite->setPosition(Settings::position(x, y));
	
	
	//Paddle animation
	CurrentFrame += PADDLE_ANIMATION_SPEED * time;
	if (CurrentFrame > 14) CurrentFrame -= 14;
	sprite->setTextureRect(sf::IntRect(0, 9 * int(CurrentFrame), 90, 9));

	//Paddle's movement considering window borders (left and right) 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (getpaddlecoordinateX() >= 0))
	{
		dir = 1; speed = PADDLE_SPEED;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (getpaddlecoordinateX() <= 550))
	{
		dir = 0; speed = PADDLE_SPEED;
	}
}

Paddle::~Paddle() 
{
	delete(File);
	delete(image);
	delete(texture);
	delete(sprite);
}


float Paddle::getpaddlecoordinateX()
{
	return x;
}

float Paddle::getpaddlecoordinateY()
{
	return y;
}
