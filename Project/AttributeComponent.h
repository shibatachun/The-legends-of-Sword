#ifndef ATTRIBUTECOMPONENT_H
#define ATTRIBUTECOMPONENT_H
class AttributeComponent
{
private:

public:
	//Leveling
	unsigned level;
	unsigned exp;
	unsigned expNext;
	unsigned AttributePoints;
	//Attributes
	
	int vitality;
	int strength;
	int dexterity;
	int agility;
	int intelligence;
	//Stats
	int hp;
	int hpMax;
	int damageMin;
	int damageMax;
	int accuracy;
	int defence;
	int luck;
	//Con /Des
	AttributeComponent(unsigned level);
	virtual ~AttributeComponent();
	//Functions
	void calcExpNext();
	void updateStates(const bool rest);
	void updateLevel();
	void update();
};
#endif

