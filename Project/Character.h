#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>

class Character {
public:
	Character();
	~Character();

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow& window);
	void move(float offsetrX, float offsetY);
	void setPosition(float x, float y);

private:
	sf::Sprite mSprite;
	sf::Texture mTexture;
	sf::Vector2f mPosition;
	float mSpeed;

	sf::IntRect mFrameRect;
	int mCurrentFrame;
	sf::Time mFrameTime;
	sf::Time mCurrentTime;

	void updateAnimation(sf::Time deltaTime);


};

#endif
