#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->maxVelocity = 0;
}

void Player::initComponents()
{
	this->createMovementComponent(250.f,10.f,4.f);
}
//Constructors / Destructors
Player::Player(float x, float y,sf::Texture& texture)
{
	this->initVariables();
	this->initComponents();
	this->setTexture(texture);
	this->setPosstion(x, y);
}

Player::~Player()
{
}
