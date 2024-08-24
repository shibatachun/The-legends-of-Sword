#ifndef ENEMYSYSTEM_H
#define ENEMYSYSTEM_H
#include "EnemySpawner.h"
#include "Rat.h"
#include "Enemy.h"
enum EnemyTypes {RAT = 0};
class EnemySystem
{
private:
	std::map<std::string, sf::Texture>& _textures;
	std::vector<Enemy*>& _activeEnemies;
		
public:

	EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures);
	
	virtual ~EnemySystem();

	//Accessors
	
	//Modifiers
	
	//Functions
	void createEnemy(short type, const float xPos, const float yPos);

	void update(const float& dt);
	void render(sf::RenderTarget* target);
};
#endif

