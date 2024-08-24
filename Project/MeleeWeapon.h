#ifndef  MELEEWEAPON_H
#define  MELLEWEAPON_H
#include "Weapon.h"
class Weapon; 
class MeleeWeapon :
    public Weapon
{
private:
   
protected:
 
public:
    MeleeWeapon(unsigned value, std::string texture_file);
    virtual ~MeleeWeapon();

    virtual MeleeWeapon* clone() = 0;
    virtual void update(const sf::Vector2f mouse_Pos_View, const sf::Vector2f center) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = NULL) = 0;
};
#endif // ! MELEEWEAPON_H



