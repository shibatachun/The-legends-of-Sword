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
public:

    Weapon(unsigned value,std::string texture_file);
    virtual ~Weapon();

    //Function
    virtual Item* clone() = 0;
    virtual void update(const sf::Vector2f mouse_Pos_View, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;
};

#endif

