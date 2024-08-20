#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"
#include "Sword.h"

class Entity;
class Player :
    public Entity
    
{
private:
    //Variables
    float maxVelocity;
    bool attacking;
    Sword sword; 
    

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
    virtual void update(const float& dt,sf::Vector2f& mouse_Pos_View);
    void render(sf::RenderTarget& target, sf::Shader* shader = NULL, const bool show_hitbox = false);

};

#endif


