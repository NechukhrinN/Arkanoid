#include "paddle.h"

Paddle::Paddle(sf::String F, float X, float Y, float W, float H)
{
	dx = 0; speed = 0;
	File = F;
	w = W; h = H;
	CurrentFrame = 0;
	image.loadFromFile("images/" + File);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	x = X; y = Y;
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

void Paddle::update(float time)
{
	switch (dir)
	{
	case 0: dx = speed; break;
	case 1: dx = -speed; break;
	default: dx = 0; break;
	}
	x += dx * time;
	speed = 0;
	sprite.setPosition(x, y);
	
	
	//Paddle animation
	CurrentFrame += 0.008*time;
	if (CurrentFrame > 14) CurrentFrame -= 14;
	sprite.setTextureRect(sf::IntRect(0, 9 * int(CurrentFrame), 90, 9));

	//Paddle move
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && (getpaddlecoordinateX() >= 0))
	{
		dir = 1; speed = 0.5;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && (getpaddlecoordinateX() <= 550))
	{
		dir = 0; speed = 0.5;
	}
}


float Paddle::getpaddlecoordinateX()
{
	return x;
}

float Paddle::getpaddlecoordinateY()
{
	return y;
}