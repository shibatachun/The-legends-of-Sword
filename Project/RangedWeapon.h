#ifndef RANGEDWEAPON_H
#define RANGEDWEAPON_H

#include "Weapon.h"
class RangedWeapon :
    public Weapon
{
private:
public:
    RangedWeapon(unsigned value, std::string texture_file);
    virtual~RangedWeapon();

    virtual RangedWeapon* clone() = 0;

    virtual void update(const sf::Vector2f mouse_Pos_View, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;

};
#endif // !RANGEDWEAPON_H



