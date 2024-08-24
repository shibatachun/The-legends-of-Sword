#include "stdafx.h"
#include "Bow.h"

Bow::Bow(unsigned value, std::string texture_file)
    :RangedWeapon(value,texture_file)
{
}

Bow::~Bow()
{
}

Bow* Bow::clone()
{
    return new Bow(*this);
}

void Bow::update(const sf::Vector2f mouse_Pos_View, const sf::Vector2f center)
{
}

void Bow::render(sf::RenderTarget& target, sf::Shader* shader)
{
}
