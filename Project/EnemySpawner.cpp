#include "stdafx.h"
#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(int grid_x, int grid_y, float gridSizeF, int tileSheetIndex,
	const sf::Texture& texture, const sf::IntRect texture_rect,
	float grid_size, int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	:Tile(grid_x, grid_y,gridSizeF,tileSheetIndex,texture,texture_rect,false,TileTypes::ENEMYSPAWN)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemeyMaxDistance = enemy_max_distance;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::spawn()
{
}

void EnemySpawner::clear()
{
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
