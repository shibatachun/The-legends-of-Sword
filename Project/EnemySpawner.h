#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

#include "Tile.h"
class Tile;
class EnemySpawner :
	Tile
{
private: 

	sf::RectangleShape shape;
	sf::Vector2i gridPosition;
	int enemyType;
	int enemyAmount;
	int enemyTimeToSpawn;
	float enemeyMaxDistance;

	
public:
	EnemySpawner(int grid_x, int grid_y, float gridSizeF, int tileSheetIndex,
		const sf::Texture& texture, const sf::IntRect texture_rect,
		float grid_size, int enemy_type, int enemy_amount , int enemy_time_to_spawn, float enemy_max_distance);
	virtual ~EnemySpawner();

	void spawn();
	void clear();
	void update();
	void render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position);
	
};
#endif
