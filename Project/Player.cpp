#include "stdafx.h"
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
	
	
	this->setPosition(x, y);
	
	this->createHitboxComponent(20.f, 25.f,65.f,75.f);
	this->createMovementComponent(300.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(0);
	this->sprite.setScale(0.5f, 0.5f);
	this->animationComponent->addAnimation("IDLE", 7.f,0,0,3,0,349,215);

	this->animationComponent->addAnimation("WALK", 5.f,5,0,8,0, 349, 215);

	this->animationComponent->addAnimation("ATTACK",1.f, 9, 0, 13, 0, 349, 215);

	//this->animationComponent->addAnimation("WALK_RIGHT", 1.f, 0, 3, 3, 3, 300, 48);

	//this->animationComponent->addAnimation("WALK_UP", 1.f, 0, 2, 3, 2, 48, 48);

	//this->animationComponent->addAnimation("WALK_DOWN", 1.f, 0, 0, 3, 0, 48, 48);
}

Player::~Player()
{
}


//Acceesor
AttributeComponent* Player::getAttributeComponent() 
{
	return this->attributeComponent;
}

//Functions
void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;
	if (this->attributeComponent->hp < 0)
	{
		this->attributeComponent->hp = 0;

	}
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->exp -= exp;
	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;
	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::gainEXP(const int exp)
{

	this->attributeComponent->gainExp(exp);


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
			this->sprite.setOrigin(210.f, 0.f);
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
		
		this->sprite.setOrigin(210.f, 0.f);
		//this->sprite.setScale(-this->sprite.getScale().x, this->sprite.getScale().y);
		this->sprite.setScale(-0.5f, 0.5f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x,this->movementComponent->getMaxVelocity());
	}	
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			//this->sprite.setScale(this->sprite.getScale().x, this->sprite.getScale().y);
			this->sprite.setScale(0.5f, 0.5f);
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

void Player::update(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		this->attributeComponent->gainExp(20);
	}
	this->attributeComponent->update();
	/*system("cls");
	std::cout << this->attributeComponent->debugPrint() << std::endl;*/
	this->movementComponent->update(dt);
	this->updataAttack();

	this->hitboxComponent->update();
	this->updateAnimation(dt);
	
		
		


	

}

void Player::render(sf::RenderTarget& target,sf::Shader* shader,  const bool show_hitbox)
{
	
	
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getCenter());
		target.draw(this->sprite, shader);
	}
	else
	{
		target.draw(this->sprite);
	}
	
	if(show_hitbox)
		this->hitboxComponent->render(target);
	
}
