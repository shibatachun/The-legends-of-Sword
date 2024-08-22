#include "stdafx.h"
#include "Enemy.h"

void Enemy::initVariables()
{
	
}
void Enemy::initAnimations()
{
	this->animationComponent->addAnimation("IDLE", 6.f, 0, 1, 8, 1, 74, 136, 0, 0);

	this->animationComponent->addAnimation("WALK", 6.f, 0, 2, 9, 2, 68, 136, 0, 0);

	this->animationComponent->addAnimation("ATTACK", 4.f, 0, 0, 4, 0, 112, 136, 0, 500.f);
}

//Constructors / Destructors
Enemy::Enemy(EnemySpawner& enemy_spawner, float x, float y, sf::Texture& texture_sheet)
	:enemySpawner(&enemy_spawner)
{
	this->initVariables();
	



	this->createHitboxComponent(20.f, 25.f, 65.f, 75.f);
	this->createMovementComponent(300.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);


	this->setPosition(x, y);
	this->initAnimations();
	//std::cout << this->skillComponent->getSkill("health") << "\n";
	//this->sprite.setScale(0.5f, 0.5f);




	//this->animationComponent->addAnimation("WALK_RIGHT", 1.f, 0, 3, 3, 3, 300, 48);

	//this->animationComponent->addAnimation("WALK_UP", 1.f, 0, 2, 3, 2, 48, 48);

	//this->animationComponent->addAnimation("WALK_DOWN", 1.f, 0, 0, 3, 0, 48, 48);
}

Enemy::~Enemy()
{


}
void Enemy::updateAnimation(const float& dt)
{



	if (this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVEING_LEFT))
	{

		this->sprite.setOrigin(80.f, 0.f);
		//this->sprite.setScale(-this->sprite.getScale().x, this->sprite.getScale().y);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			//this->sprite.setScale(this->sprite.getScale().x, this->sprite.getScale().y);
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());

	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
}
void Enemy::update(const float& dt, sf::Vector2f& mouse_Pos_View)
{
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		this->attributeComponent->gainExp(20);
	}
	this->attributeComponent->update();*/
	/*system("cls");
	std::cout << this->attributeComponent->debugPrint() << std::endl;*/
	this->movementComponent->update(dt);
	//this->updataAttack();
	this->updateAnimation(dt);
	this->hitboxComponent->update();
	//this->updateAnimation(dt);

	



}

void Enemy::render(sf::RenderTarget& target, sf::Shader* shader, const sf::Vector2f light_position,const bool show_hitbox)
{


	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", light_position);
		target.draw(this->sprite, shader);
	

		
	}
	else
	{
		target.draw(this->sprite);
		
	}

	if (show_hitbox)
		this->hitboxComponent->render(target);

}


