#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

class Entity;
class Player :
    public Entity
    
{
private:
    //Variables
    float maxVelocity;
    bool attacking;
    MovementComponent* movement;
    //Initializer functions
    void initVariables();
    void initComponents();
public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();
    //Functions
    void loseHP(const int hp);
    void loseEXP(const int exp);
    void gainHP(const int hp);
    void gainEXP(const int exp);
    void updataAttack();
    void updateAnimation(const float& dt);
    virtual void update(const float& dt);
    void render(sf::RenderTarget& target);

};

#endif


