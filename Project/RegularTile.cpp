#include "stdafx.h"
#include "RegularTile.h"

RegularTile::RegularTile(int grid_x, int grid_y, float gridSizeF, int tileSheetIndex, const sf::Texture& texture, const sf::IntRect rect, bool collision, short type)
	: Tile(grid_x,grid_y,gridSizeF,tileSheetIndex,texture,rect,collision,type)
{
}

RegularTile::~RegularTile()
{
}

const short& RegularTile::getType() const
{
	return this->type;
}

const int& RegularTile::getTileIndex() const
{
	return this->tileSheetIndex;
}

const bool& RegularTile::getCollision() const
{
	return this->collision;
}

const std::string RegularTile::getAsString() const
{
	std::stringstream ss;

	ss << this->type << " " << this->tileSheetIndex << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " " << this->collision;

	return ss.str();
}

void RegularTile::update()
{
}

void RegularTile::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
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
