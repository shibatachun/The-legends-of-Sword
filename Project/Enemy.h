#ifndef ENEMY_H
#define ENEMY_H
#include "Entity.h"
#include "EnemySpawner.h"

class Entity;
class EnemySpawner;
class Enemy :
    public Entity
{
private:
    //Variables
    //EnemySpawner* enemySpawner;
    unsigned gainExp;
    //Initializer functions
    virtual void initVariables() = 0;
    virtual void initAnimations() = 0;
public:
    Enemy();
    virtual ~Enemy();
    virtual void takeDamage(const int damge);
    virtual const bool isDead() const;
    const unsigned& getGainExp();
    virtual const AttributeComponent* getAttributeComp() const;
    virtual void updateAnimation(const float& dt) = 0;
    virtual void update(const float& dt, sf::Vector2f& mouse_Pos_View) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const sf::Vector2f light_position = sf::Vector2f(), const bool show_hitbox = false) = 0;
};
#endif
