#ifndef WEAPON_H
#define WEAPON_H
#include "Item.h"
class Weapon :
    public Item
{
private:
    void initVariables();
   
protected:
    sf::Sprite weapon_sprite;
    sf::Texture weapone_texture;

    int damageMin;
    int damageMax;
    unsigned range;


    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;


public:

    Weapon(unsigned value,std::string texture_file);
    virtual ~Weapon();
    //Accessors
    const unsigned& getRange() const;
    const unsigned& getDamageMin() const;
    const unsigned& getDamageMax() const;
    const bool getAttackTimer();
    //Function
    virtual Item* clone() = 0;
    virtual void update(const sf::Vector2f mouse_Pos_View, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;
};

#endif

