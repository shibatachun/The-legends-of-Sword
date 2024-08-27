 #include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
	this->range = 10;
	this->damageMin = 1;
	this->damageMax = 2;

	//Timer
	this->attackTimer.restart();
	this->attackTimerMax = 500;
}


Weapon::Weapon(unsigned value, std::string texture_file)
	:Item(value)
{
	this->initVariables();
	if (!this->weapone_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD TEXTURE::" << texture_file  << std::endl;
	this->weapon_sprite.setTexture(this->weapone_texture);
}

Weapon::~Weapon()
{
}
//Accessor
const unsigned& Weapon::getRange() const
{
	return this->range;
}

const unsigned& Weapon::getDamageMin() const
{
	return this->damageMin;
}

const unsigned& Weapon::getDamageMax() const
{
	return this->damageMax;
}

const bool Weapon::getAttackTimer()
{
	//std::cout << this->attackTimer.getElapsedTime().asMilliseconds() << std::endl;
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;

	}
	return false;
}
