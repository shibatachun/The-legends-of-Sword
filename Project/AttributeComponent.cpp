#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(unsigned level)
{
	this->level = level;
	this->exp = 0;
	this->expNext = 0;
	this->AttributePoints = 3;

	this->vitality = 1;

	this->strength = 1;

	this->dexterity = 1;
	this->agility = 1;
	this->intelligence = 1;
	this->updateStates(true);
}

AttributeComponent::~AttributeComponent()
{
	this->expNext = (50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12);
}

void AttributeComponent::calcExpNext()
{
}

void AttributeComponent::updateStates(const bool reset)
{
	this->hpMax		= this->vitality * 10 + this->vitality + this->strength / 2+ this->intelligence / 5;
	this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->accuracy	= this->dexterity * 4 + this->dexterity / 2 + this->intelligence / 5;
	this->defence	= this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck		= this->intelligence * 2 + this->intelligence / 5;

	if (reset)
	{
		this->hp = this->hpMax;

	}
}

void AttributeComponent::updateLevel()
{
	while((this->exp >= this->expNext))
	{   
		++this->level;
		this->exp -= this->expNext;
		this->expNext = (50 / 3) * (pow(this->level, 3) - 6 * pow(this->level, 2) + (this->level * 17) - 12);
		++this->AttributePoints;
	}

}

void AttributeComponent::update()
{
	this->updateLevel();
	

}
 