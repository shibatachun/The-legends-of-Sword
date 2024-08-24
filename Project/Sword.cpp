#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned value, std::string texture_file)
	:MeleeWeapon(value,texture_file)
{


	this->weapon_sprite.setOrigin((this->weapon_sprite.getGlobalBounds().width / 2.f) - 10.f,
		(this->weapon_sprite.getGlobalBounds().height / 2.f) + 20.f);
	this->weapon_sprite.setScale(2.f, 2.f);


}

Sword::~Sword()
{
}

Sword* Sword::clone()
{
	return new Sword(*this);
}

void Sword::update(const sf::Vector2f mouse_Pos_View, const sf::Vector2f center)
{

	this->weapon_sprite.setPosition(center);

	float dx = mouse_Pos_View.x - this->weapon_sprite.getPosition().x;
	float dy = mouse_Pos_View.y - this->weapon_sprite.getPosition().y;

	const float PI = 3.14159265f;
	float deg = atan2(dy, dx) * 180.f / PI;

	this->weapon_sprite.setRotation(deg);
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if(shader)
		target.draw(this->weapon_sprite,shader);
	else
		target.draw(this->weapon_sprite);

}
