#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->maxVelocity = 0;
	this->attacking = false;
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
	
	this->createHitboxComponent(120.f, 120.f,48.f,48.f);
	this->createMovementComponent(300.f, 10.f, 4.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 7.f,0,0,6,0,300,300);

	this->animationComponent->addAnimation("WALK", 5.f,0,1,7,1, 300, 300);

	this->animationComponent->addAnimation("ATTACK",1.f, 0, 2, 5, 2, 300, 300);

	//this->animationComponent->addAnimation("WALK_RIGHT", 1.f, 0, 3, 3, 3, 300, 48);

	//this->animationComponent->addAnimation("WALK_UP", 1.f, 0, 2, 3, 2, 48, 48);

	//this->animationComponent->addAnimation("WALK_DOWN", 1.f, 0, 0, 3, 0, 48, 48);
}

Player::~Player()
{
}
void Player::updataAttack()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J))
	{
		this->attacking = true;

	}
}
void Player::updateAnimation(const float& dt)
{

	if (this->attacking)
	{
		//Set origin depending on direction
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
		}
		else //Facing right
		{
			this->sprite.setOrigin(300.f, 0.f);
		}
		//Animate and check for animation end
		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->attacking = false;
		}		
	}

	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVEING_LEFT))
	{
		
		this->sprite.setOrigin(300.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x,this->movementComponent->getMaxVelocity());
	}	
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
		
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
}
//Functions
void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->updataAttack();

	this->hitboxComponent->update();
	this->updateAnimation(dt);
	
		
		


	

}
