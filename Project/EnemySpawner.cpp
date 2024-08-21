#include "stdafx.h"
#include "EnemySpawner.h"


EnemySpawner::EnemySpawner(sf::Vector2i grid_position, float grid_size,int type, int amount, int time_to_spawn, float max_distance)
{
	this->shape.setSize(sf::Vector2f(grid_size, grid_size));
	this->shape.setFillColor(sf::Color::Red);
	this->gridPosition = gridPosition;
	this->type = type;
	this->amount = amount;
	this->timeToSpawn = time_to_spawn;
	this->maxDistance = max_distance;
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



void EnemySpawner::update(const float& dt)
{
}

void EnemySpawner::render(const sf::RenderTarget& target)
{
	
}
