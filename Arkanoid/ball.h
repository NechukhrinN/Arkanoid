#ifndef  BALL
#define BALL
#include <SFML\Graphics.hpp>

class Ball
{ 
public:
	float w, h, dx, dy;
	float x, y;
	sf::String* File;
	sf::Image* image;
	sf::Texture* texture;
	sf::Sprite* sprite;
	float CurrentFrame = 0;
	Ball(const sf::String& F, const float& X, const float& Y, const float& W, const float& H);
	~Ball();
	void update();
	void update(const float& time);
};

typedef std::unique_ptr<Ball> Ball_ptr;

#endif
