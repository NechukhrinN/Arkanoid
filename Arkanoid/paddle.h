#ifndef  PADDLE
#define PADDLE
#include <SFML\Graphics.hpp>

class Paddle
{
private: float x, y;
public:
	bool life;
	int dir, pScore, health;
	float w, h, dx, speed, CurrentFrame = 0;
	sf::String* File;
	sf::Image* image;
	sf::Texture* texture;
	sf::Sprite* sprite;

	Paddle(const sf::String& F, const float& X, const float& Y, const float& W, const float& H);
	~Paddle();
	void update(const float& time);
	float getpaddlecoordinateX();
	float getpaddlecoordinateY();
};

typedef std::unique_ptr<Paddle> Paddle_ptr;

#endif
