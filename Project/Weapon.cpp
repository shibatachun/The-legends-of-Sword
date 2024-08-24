#include "stdafx.h"
#include "Weapon.h"

void Weapon::initVariables()
{
}

Weapon::Weapon(unsigned value, std::string texture_file)
	:Item(value)
{
	if (!this->weapone_texture.loadFromFile(texture_file))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD TEXTURE::" << texture_file  << std::endl;
	this->weapon_sprite.setTexture(this->weapone_texture);
}

Weapon::~Weapon()
{
}
