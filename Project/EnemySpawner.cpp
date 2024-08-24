#include "stdafx.h"
#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, int tileSheetIndex,
	const sf::Texture& texture, const sf::IntRect texture_rect,
	int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	:Tile(grid_x, grid_y,gridSizeF,tileSheetIndex,texture,texture_rect,false,TileTypes::ENEMYSPAWN)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemeyMaxDistance = enemy_max_distance;
	this->spawned = false;
}	

EnemySpawner::~EnemySpawner()
{
}


const std::string EnemySpawner::getAsString() const
{
	std::stringstream ss;

	/*
	x, y ,z
	type,
	rect x, rect y,
	enemy type,
	enemy amount
	enemy time to spawn
	enemy max distance
	*/
	ss << this->type << " " << this->tileSheetIndex << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<<this->enemyType << " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemeyMaxDistance;

	return ss.str();
	return std::string();
}

const bool& EnemySpawner::getSpawned() const
{
	return this->spawned;
}




void EnemySpawner::setSpawned(const bool spawned)
{
	this->spawned = spawned;

}

//Functions
void EnemySpawner::update()
{
}

void EnemySpawner::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f player_position)
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
