#include "stdafx.h"
#include "Item.h"

void Item::initVariables()
{

}

Item::Item(unsigned value)
{
	this->initVariables();
	this->value = value;
	this->type = ItemTypes::ITEM_DEFAULT;
}

Item::~Item()
{
}
