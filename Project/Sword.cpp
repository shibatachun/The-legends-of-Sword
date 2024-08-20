#include "stdafx.h"
#include "Sword.h"

Sword::Sword()
{
	if (!this->weapone_texture.loadFromFile("Resources/images/Sprites/Player/Sniper.png"))
		std::cout << "ERROR::PLAYER::COULD NOT LOAD TEXTURE";
	this->weapon_sprite.setTexture(this->weapone_texture);

	this->weapon_sprite.setOrigin((this->weapon_sprite.getGlobalBounds().width / 2.f) - 10.f,
		(this->weapon_sprite.getGlobalBounds().height / 2.f) + 20.f);
	this->weapon_sprite.setScale(2.f, 2.f);


}

Sword::~Sword()
{
}

void Sword::update(const sf::Vector2f mouse_Pos_View, const sf::Vector2f center)
{

	this->weapon_sprite.setPosition(center);

	float dx = mouse_Pos_View.x - this->weapon_sprite.getPosition().x;
	float dy = mouse_Pos_View.y - this->weapon_sprite.getPosition().y;

	const float PI = 3.14159265;
	float deg = atan2(dy, dx) * 180 / PI;

	this->weapon_sprite.setRotation(deg);
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if(shader)
		target.draw(this->weapon_sprite,shader);
	else
		target.draw(this->weapon_sprite);

}
