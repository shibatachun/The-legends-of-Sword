#include "Player.h"
//Initializer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	
}
//Constructors / Destructors
Player::Player(float x, float y,sf::Texture* texture)
{
	this->initVariables();
	this->initComponents();
	this->createSprite(texture);
	this->setPosstion(x, y);
}

Player::~Player()
{
}
