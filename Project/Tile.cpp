#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
	this->tileSheetIndex = 0;
}

Tile::Tile(int x, int y, float gridSizeF, int tileSheetIndex, const sf::Texture& texture, const sf::IntRect texture_rect,
	bool collision, short type)
{
	/*this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);*/
	//this->shape.setOutlineThickness(1.f);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(static_cast<float>(x)*gridSizeF, static_cast<float>(y) *gridSizeF);
	this->shape.setTexture(texture);
	this->shape.setTextureRect(texture_rect);
	this->tileSheetIndex = tileSheetIndex;
	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{
}
const short& Tile::getType() const
{

	return this->type;

}
	
	


const int& Tile::getTileIndex() const
{
	return this->tileSheetIndex;
}
//Accessors
const sf::Vector2f& Tile::getPosition() const
{
	return this->shape.getPosition();
}

const bool& Tile::getCollision() const
{
	return this->collision;
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}



//Functions

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}


const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss<<this->type << " " << this->tileSheetIndex <<" "<< this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision  ;

	return ss.str();
}
void Tile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
{
	if (shader)
	{
		shader->setUniform("lightPos", player_position);
		shader->setUniform("hasTexture", true);
		target.draw(this->shape, shader);
	}
	else
	{
		target.draw(this->shape);

	}

}

void Tile::update()
{
	//this->shape.setColor(sf::Color::Red);
}
