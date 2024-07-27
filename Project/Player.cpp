#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->maxVelocity = 0;
}

void Player::initComponents()
{
	
}
//Constructors / Destructors
Player::Player(float x, float y,sf::Texture& texture_sheet)
{
	this->initVariables();
	this->initComponents();
	
	
	this->setPosstion(x, y);

	this->createHitboxComponent(75.f, 75.f,100.f,100.f);
	this->createMovementComponent(250.f, 10.f, 4.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 1.f,0,0,6,0,300,300);
	this->animationComponent->addAnimation("WALK_LEFT", 1.f,0,1,7,1, 300, 300);
}

Player::~Player()
{
}
//Functions
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->hitboxComponent->update();

	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if(this->movementComponent->getState(MOVEING_LEFT))
		this->animationComponent->play("WALK_LEFT", dt);


	

}
