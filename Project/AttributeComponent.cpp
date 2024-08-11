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
	this->updateStates();
}

AttributeComponent::~AttributeComponent()
{

}

void AttributeComponent::calculateExpNext()
{
}

void AttributeComponent::updateStates()
{
}

void AttributeComponent::levelup()
{
}

void AttributeComponent::update()
{
}
 