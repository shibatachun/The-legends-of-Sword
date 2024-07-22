#include "Character.h"
#include <iostream>

Character::Character() :mSpeed(1.0f), mCurrentFrame(0), mFrameTime(sf::seconds(0.1f)) {
	if (!mTexture.loadFromFile("..\\Tiny RPG Character Asset Pack v1.03 -Free Soldier&Orc\\Characters(100x100)\\Soldier\\Soldier with shadows\\Soldier-Idle.png"))
	{
		std::cerr << "Failed to load character texture" << std::endl;	
	}
	mSprite.setTexture(mTexture);
	mPosition = sf::Vector2f(400, 300);

	mFrameRect = sf::IntRect(0, 0, 64,64);
	mSprite.setTextureRect(mFrameRect);
	mSprite.setPosition(mPosition);


}

Character::~Character(){}
void Character::update(sf::Time deltaTime) {
	updateAnimation(deltaTime);

	mSprite.setPosition(mPosition);



}

void Character::setPosition(float x, float y)
{
	mPosition = sf::Vector2f(x, y);
}
void Character::render(sf::RenderWindow& window) {
	window.draw(mSprite);


}

void Character::move(float offsetX, float offsetY) {
	mPosition.x += offsetX * mSpeed * mFrameTime.asSeconds();
	mPosition.y += offsetY * mSpeed * mFrameTime.asSeconds();

}

void Character::updateAnimation(sf::Time deltaTime)
{
	mCurrentTime += deltaTime;
	if (mCurrentTime >= mFrameTime) {
		mCurrentTime -= mFrameTime;
		mCurrentFrame++;
		if (mCurrentFrame >= 6) {
			mCurrentFrame = 0;

		}
		mFrameRect.left = mCurrentFrame * 64;
		mSprite.setTextureRect(mFrameRect);

	}
}