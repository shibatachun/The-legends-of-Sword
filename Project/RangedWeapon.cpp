#include "stdafx.h"
#include "RangedWeapon.h"

RangedWeapon::RangedWeapon(unsigned value, std::string texture_file)
	:Weapon(value,texture_file)
{
	this->type = ItemTypes::RANGEDWEAPON;
}

RangedWeapon::~RangedWeapon()
{
}
