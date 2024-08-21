#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H

class EnemySpawner
{
private: 

	sf::RectangleShape shape;
	sf::Vector2i gridPosition;
	int type;
	int amount;
	int timeToSpawn;
	float maxDistance;

	
public:
	EnemySpawner(sf::Vector2i gird_position, float grid_size, int type, int amount , int time_to_spawn, float max_distance);
	virtual ~EnemySpawner();

	void spawn();
	void clear();
	void update(const float& dt);
	void render(const sf::RenderTarget& target);
	
};
#endif

