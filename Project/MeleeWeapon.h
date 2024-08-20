#ifndef  MELEEWEAPON_H
#define  MELLEWEAPON_H
#include "Item.h"
class Item; 
class MeleeWeapon :
    public Item
{
private:
   
protected:
    sf::Sprite weapon_sprite;
    sf::Texture weapone_texture;

    int damageMin;
    int damageMax;
public:
    MeleeWeapon();
    virtual ~MeleeWeapon();

    virtual void update(const sf::Vector2f mouse_Pos_View, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;
};
#endif // ! MELEEWEAPON_H



