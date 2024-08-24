#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(unsigned value, std::string texture_file)
	:Weapon(value,texture_file)
{
	this->type = ItemTypes::MEELEEWEAPON;
}

MeleeWeapon::~MeleeWeapon()
{
}
