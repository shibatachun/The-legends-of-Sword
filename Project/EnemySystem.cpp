#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures)
	:_textures(textures),_activeEnemies(activeEnemies)
{
	_textures = textures;
	_activeEnemies = activeEnemies;
}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::createEnemy(const short type, const float xPos, const float yPos)
{
	switch (type)
	{
	case EnemyTypes::RAT:
		_activeEnemies.push_back(new Rat(xPos,yPos,_textures["ENEMY"]));
		break;
	default:
		std::cout << "ERROR::ENEMYSTSTEM::CREATEENEMY::TYPE DOES NOT EXIT" << "\n";
		break;
	}
}

void EnemySystem::update(const float& dt)
{
}

void EnemySystem::render(sf::RenderTarget* target)
{
}
