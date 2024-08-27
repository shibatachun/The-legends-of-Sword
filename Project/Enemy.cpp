#include "stdafx.h"
#include "Enemy.h"



void Enemy::initVariables()
{
	this->gainExp = 10;
}



void Enemy::initAnimations()
{
}

//Constructors / Destructors
Enemy::Enemy()
	
{
	this->initVariables();
	this->initAnimations();
}

Enemy::~Enemy()
{


}

/*
* The enemy taking damage
*/
void Enemy::takeDamage(const int damge)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(damge);
	}
}

const bool Enemy::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}
	
}

const unsigned& Enemy::getGainExp()
{
	return this->gainExp;
}

const AttributeComponent* Enemy::getAttributeComp() const
{
	if (this->attributeComponent)
		return this->attributeComponent;
	else
	{
		std::cout << "ERROR::ENEMY::ATTRIBUTECOMPONENT IS NOT INITIALIZED" << "\n";
		return nullptr;

	}
}


